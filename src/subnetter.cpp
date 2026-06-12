#include "subnetter.hpp"
#include <sstream>
#include <cmath>
#include <algorithm>
#include <cstdint>

Subnetter::Subnetter(const std::string& baseIP, bool isAscending) {
  this->baseIP = convertIPtoUINT(baseIP);
  this->isAscending = isAscending;
}

void Subnetter::subnet(std::vector<Group>& groups) {
  // Orders the groups according to the amount of IPs required, the direction
  // is assigned by "isAscending"
  std::sort(groups.begin(), groups.end(), [=](const Group& a, const Group& b) {
    // If it isAscending returns true and orders from smaller to bigger, otherwise
    // it returns false and orders from bigger to smaller
    return isAscending ? a.amountIP < b.amountIP : a.amountIP > b.amountIP;
  });

  uint32_t currentIP = this->baseIP;
  for (size_t i = 0; i < groups.size(); ++i) {
    int mask = calculateMask(groups[i].amountIP);
    // Get the total amount of directions for the subnet (1 << n = 2^n)
    uint32_t block = 1 << (32 - mask);

    // Verifies if there is enough space to assign the IPs
    if (currentIP > (UINT32_MAX - block + 1)) {
      groups[i].assignedIP = "NO SPACE";
      groups[i].mask = -1;
      groups[i].amountIP = block;
      continue;
    }

    groups[i].mask = mask;
    groups[i].amountIP = block;
    groups[i].assignedIP = convertUINTtoIP(currentIP);
    currentIP += block;
  }
}

uint32_t Subnetter::convertIPtoUINT(const std::string& ip) {
  int a, b, c, d;
  // Read the string IP with format aaa.bbb.ccc.ddd
  sscanf(ip.c_str(), "%d.%d.%d.%d", &a, &b, &c, &d);
  // Join all the 4 integers into a single uint of 32 bits
  return (a << 24) | (b << 16) | (c << 8) | d;
}

std::string Subnetter::convertUINTtoIP(uint32_t ip) {
  // Assign 8 bits at a time to form the resulting IP, using 0xFF to aislate the
  // last 8 bits
  return std::to_string((ip >> 24) & 0xFF) + "." +
          std::to_string((ip >> 16) & 0xFF) + "." +
          std::to_string((ip >> 8) & 0xFF) + "." +
          std::to_string(ip & 0xFF);
}

int Subnetter::calculateMask(int amountIP) {
  // Calculate how many bits are needed to represent the amountIP + 2 directions
  // for network and broadcast, that can't be assigned toi hosts
  int bits = std::ceil(std::log2(amountIP + 2));
  return 32 - bits;
}