#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#ifdef _WIN32
const std::string HOSTS_FILE = "C:\\Windows\\System32\\drivers\\etc\\hosts";
#else
const std::string HOSTS_FILE = "/etc/hosts";
#endif

// Function to block websites by writing to the hosts file
void blockWebsites(const std::vector<std::string>& websites) {
    std::ofstream hostsFile;

    // Open the hosts file in append mode
    hostsFile.open(HOSTS_FILE, std::ios::app);
    if (!hostsFile.is_open()) {
        std::cerr << "Error: Could not open hosts file. Run as administrator or root." << std::endl;
        return;
    }

    // Loop through the list of websites to block
    for (const auto& website : websites) {
        hostsFile << "127.0.0.1 " << website << "\n";
        hostsFile << "127.0.0.1 www." << website << "\n";
    }

    hostsFile.close();
    std::cout << "Websites blocked successfully!" << std::endl;
}

// Function to unblock websites by removing entries from the hosts file
void unblockWebsites(const std::vector<std::string>& websites) {
    std::ifstream inFile(HOSTS_FILE);
    if (!inFile.is_open()) {
        std::cerr << "Error: Could not open hosts file. Run as administrator or root." << std::endl;
        return;
    }

    std::string line;
    std::vector<std::string> lines;

    // Read the hosts file line by line
    while (std::getline(inFile, line)) {
        bool isBlocked = false;

        // Check if the line contains any of the blocked websites
        for (const auto& website : websites) {
            if (line.find(website) != std::string::npos) {
                isBlocked = true;
                break;
            }
        }

        // Only add lines that don't contain blocked websites
        if (!isBlocked) {
            lines.push_back(line);
        }
    }
    inFile.close();

    // Rewrite the hosts file with the unblocked lines
    std::ofstream outFile(HOSTS_FILE, std::ios::trunc);
    for (const auto& outLine : lines) {
        outFile << outLine << "\n";
    }

    std::cout << "Websites unblocked successfully!" << std::endl;
}

// Main function to interact with the user
int main() {
    std::vector<std::string> websites;
    int choice;

    std::cout << "Website Blocker" << std::endl;
    std::cout << "1. Block websites\n2. Unblock websites\nChoose an option: ";
    std::cin >> choice;

    if (choice != 1 && choice != 2) {
        std::cerr << "Invalid choice." << std::endl;
        return 1;
    }

    std::cout << "Enter the websites to block/unblock (one per line, type 'done' to finish):" << std::endl;

    std::string website;
    while (true) {
        std::cin >> website;
        if (website == "done") {
            break;
        }
        websites.push_back(website);
    }

    if (choice == 1) {
        blockWebsites(websites);
    } else if (choice == 2) {
        unblockWebsites(websites);
    }

    return 0;
}
