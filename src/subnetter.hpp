#ifndef SUBNETTER_HPP
#define SUBNETTER_HPP

#include <string>
#include <vector>
#include <cstdint>

/**
 * @brief Represents a group that requires a subnet.
 */
struct Group {
  std::string groupName;   ///< Name of the group.
  int amountIP;            ///< Number of IP addresses needed by the group.
  std::string assignedIP;  ///< The base IP assigned to the group.
  int mask;                ///< The subnet mask length.
};

class Subnetter {
 public:
   /**
   * @brief Constructs a Subnetter with the given base IP and sorting order.
   * 
   * @param baseIP The starting IP address from which to begin subnetting.
   * @param isAscending If true, sorts groups in ascending order of size, otherwise it is descending.
   */
  Subnetter(const std::string& baseIP, bool isAscending);

  /**
   * @brief Assigns subnets to the given list of groups.
   * 
   * @param groups The list of groups to be subnetted.
   */
  void subnet(std::vector<Group>& groups);

 private:
  uint32_t baseIP;   ///< The base IP address in 32-bit uint format.
  bool isAscending;  ///< Determines whether to sort groups in ascending order.

  /**
   * @brief Converts a dotted decimal IP string to a 32-bit uint.
   * 
   * @param ip The IP address in dotted decimal format (192.168.0.1).
   * @return The IP address as a 32-bit uint.
   */
  uint32_t convertIPtoUINT(const std::string& ip);

  /**
   * @brief Converts a 32-bit uuint IP address to dotted decimal format.
   * 
   * @param ip The IP address as a 32-bit uint.
   * @return The IP address in dotted decimal format.
   */
  std::string convertUINTtoIP(uint32_t ip);

  /**
   * @brief Calculates the smallest subnet mask that can accommodate a given number of IP addresses.
   * 
   * @param amountIP The number of required IP addresses.
   * @return The subnet mask (24 for /24).
   */
  int calculateMask(int amountIP);
};

#endif