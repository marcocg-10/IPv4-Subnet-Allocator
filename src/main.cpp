#include <iostream>
#include <fstream>
#include <vector>
#include "subnetter.hpp"

int main(int argc, char* argv[]) {
  if (argc < 2) {
    std::cerr << "Uso: " << argv[0] << " archivo_entrada.txt\n";
    return 1;
  }

  // Read file name from where we will be receiving the arguments
  std::string input_filename = argv[1];
  std::ifstream input(input_filename);

  if (!input) {
    std::cerr << "No se pudo abrir " << argv[1] << "\n";
    return 1;
  }

  // Generate the output file name automatically
  std::string output_filename;
  size_t pos = input_filename.find("input");
  if (pos != std::string::npos) {
    output_filename = argv[1];
    output_filename.replace(pos, 5, "output");  // Replaces "input" for "output"
  } else {
    output_filename = "output.txt";  // Default
  }

  std::ofstream output(output_filename);
  if (!output) {
    std::cerr << "No se pudo crear el archivo de salida: " << output_filename << "\n";
    return 1;
  }

  // Read the base IP and the order from the file
  std::string baseIP, order;
  input >> baseIP >> order;

  bool isAscending;
  if (order == "ASC") {
    isAscending = true;
  } else if (order == "DESC") {
    isAscending = false;
  } else {
    std::cerr << "Error: el orden debe ser 'ASC' (ascendente) o 'DESC' (descendente). Se recibió: '" << order << "'\n";
    return 1;
  }

  std::vector<Group> groups;
  std::string groupName;
  int amountIP;

  // Read all the groups given from the file
  while (input >> groupName >> amountIP) {
    groups.push_back({groupName, amountIP, "", 0});
  }

  // Initialize a subnetter that will be assigned to subnet the groups received
  // from the file using the baseIP and the order
  Subnetter subnetter(baseIP, isAscending);
  subnetter.subnet(groups);

  // Write the results received from the subnetter to the output file
  for (const auto& g : groups) {
    output << g.groupName << " "
          << g.amountIP << " "
          << g.assignedIP << " /"
          << g.mask << "\n";
  }

  return 0;
}
