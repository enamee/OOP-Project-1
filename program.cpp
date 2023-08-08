#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <sstream>

int i, cpuInRep, motherboardInRep, ramInRep, ssdInRep;
double totalPrice;
int discount;

class CPU;
class Motherboard;
class RAM;
class SSD;
class PCConfig;
void addCPUFromFile(std::string);
void addMotherboardFromFile(std::string);
void addRAMFromFile(std::string);
void addSSDFromFile(std::string);
void title();
void homePage();
void checkoutPage();
void componentPage();
void cpuPage();
void motherboardPage();
void ramPage();
void ssdPage();
double calculateTotalCost(PCConfig);
double calculateDiscountedPrice();
void generateLog(PCConfig);

class CPU {
public:
    CPU() {}
    CPU(std::string name, std::string socketType, int price)
    : name(name), socketType(socketType), price(price) {}
    std::string getName() { return name; }
    std::string getSocketType() { return socketType; }
    int getPrice() { return price; }
    void showInfo() {
        std::cout << "Model: " << name << "\n";
        std::cout << "Socket Type: " << socketType << "\n";
        std::cout << "Price: " << price << " BDT\n";
    }
    void unselect() {
        name = "";
        socketType = "";
        price = 0;
    }
    friend void addCPUFromFile(std::string);
private:
    std::string name, socketType;
    int price;
};

class Motherboard {
public:
    Motherboard() {}
    Motherboard(std::string name, std::string socketType, int price)
    : name(name), socketType(socketType), price(price) {}
    std::string getName() { return name; }
    std::string getSocketType() { return socketType; }
    int getPrice() { return price; }
    void showInfo() {
        std::cout << "Model: " << name << "\n";
        std::cout << "Socket Type: " << socketType << "\n";
        std::cout << "Price: " << price << " BDT\n";
    }
    void unselect() {
        name = "";
        socketType = "";
        price = 0;
    }
    friend void addMotherboardFromFile(std::string);
private:
    std::string name, socketType;
    int price;
};

class RAM {
public:
    RAM() {}
    RAM(std::string name, int capacity, int price)
    : name(name), capacity(capacity), price(price) {}
    std::string getName() { return name; }
    int getCapacity() { return capacity; }
    int getPrice() { return price; }
    void showInfo() {
        std::cout << "Model: " << name << "\n";
        std::cout << "Capacity: " << capacity << "\n";
        std::cout << "Price: " << price << " BDT\n";
    }
    friend void addRAMFromFile(std::string fileName);
private:
    std::string name;
    int capacity, price;
};

class SSD {
public:
    SSD() {}
    SSD(std::string name, int capacity, int price)
    : name(name), capacity(capacity), price(price) {}
    std::string getName() { return name; }
    int getCapacity() { return capacity; }
    int getPrice() { return price; }
    void showInfo() {
        std::cout << "Model: " << name << "\n";
        std::cout << "Capacity: " << capacity << "\n";
        std::cout << "Price: " << price << " BDT\n";
    }
    friend void addSSDFromFile(std::string fileName);
private:
    std::string name;
    int capacity, price;
};

class PCConfig {
public:
    void addCPU(CPU cpu) {
        char yn;
        if (motherboardIsSelected == false) {
            selectedCPU = cpu;
            CPUIsSelected = true;
            std::cout << "CPU selected successfully." << std::endl;
        }
        else {
            if (cpu.getSocketType() == selectedMotherboard.getSocketType()) {
                selectedCPU = cpu;
                CPUIsSelected = true;
                std::cout << "CPU selected successfully." << std::endl;
            }
            else {
                std::cout << "This CPU isn't compatible with selected Motherboard!"
                "CPU & Motherboard need to be of same socket type." << std::endl;
                std::cout << "Do you want to unselect the selected motherboard and select this cpu?(Y/y for yes): ";
                std::cin >> yn;
                if (yn == 'y' || yn == 'Y') {
                    selectedMotherboard.unselect();
                    motherboardIsSelected = false;
                    selectedCPU = cpu;
                    CPUIsSelected = true;

                }
            }
        }
    }
    bool getCPUIsSelected() { return CPUIsSelected; }
    void addMotherboard(Motherboard motherboard) {
        char yn;
        if (CPUIsSelected == false) {
            selectedMotherboard = motherboard;
            motherboardIsSelected = true;
            std::cout << "Motherboard selected successfully." << std::endl;
        }
        else {
            if (selectedCPU.getSocketType() == motherboard.getSocketType()) {
                selectedMotherboard = motherboard;
                motherboardIsSelected = true;
                std::cout << "Motherboard selected successfully." << std::endl;
            }
            else {
                std::cout << "Selected CPU isn't compatible with this Motherboard!"
                "CPU & Motherboard need to be of same socket type." << std::endl;
                std::cout << "Do you want to unselect the selected cpu and select this moyherboard?(Y/y for yes): ";
                std::cin >> yn;
                if (yn == 'y' || yn == 'Y') {
                    selectedCPU.unselect();
                    CPUIsSelected = false;
                    selectedMotherboard = motherboard;
                    motherboardIsSelected = true;
                }
            }
        }
    }
    bool getMotherbardIsSelected() { return motherboardIsSelected; }
    void addRAM(RAM ram, int quantity) {
        for (i = 0; i < quantity; i++) {
            selectedRAM[numRAMs] = ram;
            numRAMs++;
        }
    }
    int getNumRAMs() { return numRAMs; }
    void addSSD(SSD ssd, int quantity) {
        for (i = 0; i < quantity; i++) {
            selectedSSD[numSSDs] = ssd;
            numSSDs++;
        }
    }
    int getNumSSDs() { return numSSDs; }
    void display() {
        if (CPUIsSelected == true) {
            std::cout << "CPU: " << selectedCPU.getName() << "\tPrice: " << selectedCPU.getPrice() << " BDT" << std::endl;
        }
        if (motherboardIsSelected == true) {
            std::cout << "Motherboard: " << selectedMotherboard.getName() << "\tPrice: " << selectedMotherboard.getPrice() << " BDT" << std::endl;
        }
        if (numRAMs > 0) {
            for (i = 0; i < numRAMs; ++i) {
                std::cout << "RAM: " << selectedRAM[i].getName() << "\tPrice: " << selectedRAM[i].getPrice() << " BDT" << std::endl;
            }
        }
        if (numSSDs > 0) {
            for (i = 0; i < numSSDs; ++i) {
                std::cout << "SSD: " << selectedSSD[i].getName() << "\tPrice: " << selectedSSD[i].getPrice() << " BDT" << std::endl;
            }
        }
    }
    void shortDisplay() {
        std::cout << "Your selected items:" << std::endl;
        if (CPUIsSelected == true) {
            std::cout << "CPU: " << selectedCPU.getName() << std::endl;
        }
        if (motherboardIsSelected == true) {
            std::cout << "Motherboard: " << selectedMotherboard.getName() << std::endl;
        }
        if (numRAMs > 0) {
            for (i = 0; i < numRAMs; ++i) {
                std::cout << "RAM: " << selectedRAM[i].getName() << std::endl;
            }
        }
        if (numSSDs > 0) {
            for (i = 0; i < numSSDs; ++i) {
                std::cout << "SSD: " << selectedSSD[i].getName() << std::endl;
            }
        }
    }
    friend double calculateTotalCost(PCConfig);
    friend void generateLog(PCConfig);
private:
    CPU selectedCPU;
    bool CPUIsSelected = false;
    Motherboard selectedMotherboard;
    bool motherboardIsSelected = false;
    RAM selectedRAM[100];
    SSD selectedSSD[100];
    int numRAMs = 0;
    int numSSDs = 0;
};

CPU cpuRepository[100];
Motherboard motherboardRepository[100];
RAM ramRepository[100];
SSD ssdRepository[100];
PCConfig customerConfig;

int main() {
    addCPUFromFile("Private/cpu_repository.txt");
    addMotherboardFromFile("Private/motherboard_repository.txt");
    addRAMFromFile("Private/ram_repository.txt");
    addSSDFromFile("Private/ssd_repository.txt");
    homePage();
    return 0;
}

void addCPUFromFile(std::string fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
    else {
        cpuInRep = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss;
            ss << line;
            std::string name, socketType;
            int price;
            char delimiter = ',';
            std::getline(ss, name, delimiter);
            std::getline(ss, socketType, delimiter);
            ss >> price;
            cpuRepository[cpuInRep].name = name;
            cpuRepository[cpuInRep].socketType = socketType;
            cpuRepository[cpuInRep].price = price;
            cpuInRep++;
        }
    }
}

void addMotherboardFromFile(std::string fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
    else {
        motherboardInRep = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss;
            ss << line;
            std::string name, socketType;
            int price;
            char delimiter = ',';
            std::getline(ss, name, delimiter);
            std::getline(ss, socketType, delimiter);
            ss >> price;
            motherboardRepository[motherboardInRep].name = name;
            motherboardRepository[motherboardInRep].socketType = socketType;
            motherboardRepository[motherboardInRep].price = price;
            motherboardInRep++;
        }
    }
}

void addRAMFromFile(std::string fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
    else {
        ramInRep = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss;
            ss << line;
            std::string name;
            int capacity, price;
            char delimiter = ',';
            std::getline(ss, name, delimiter);
            ss >> capacity >> delimiter >> price;
            ramRepository[ramInRep].name = name;
            ramRepository[ramInRep].capacity = capacity;
            ramRepository[ramInRep].price = price;
            ramInRep++;
        }
    }
}

void addSSDFromFile(std::string fileName) {
    std::ifstream file(fileName);
    if (!file) {
        std::cerr << "Error opening file: " << fileName << std::endl;
    }
    else {
        ssdInRep = 0;
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss;
            ss << line;
            std::string name;
            int capacity, price;
            char delimiter = ',';
            std::getline(ss, name, delimiter);
            ss >> capacity >> delimiter >> price;
            ssdRepository[ssdInRep].name = name;
            ssdRepository[ssdInRep].capacity = capacity;
            ssdRepository[ssdInRep].price = price;
            ssdInRep++;
        }
    }
}

void title() {
    system("cls");
    std::cout << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << "|    PC Builder - Build your Computer    |" << std::endl;
    std::cout << "------------------------------------------" << std::endl;
    std::cout << std::endl;
}

void homePage() {
    int option;
    std::string userInput;
    title();
    std::cout << "Home Page" << std::endl;
    std::cout << std::endl;
    std::cout << "1. Select Components" << std::endl;
    std::cout << "2. Checkout" << std::endl;
    std::cout << std::endl;
    std::cout << "Press only Enter to exit." << std::endl;
    std::cout << std::endl;
    std::cout << "Input: ";
    fflush(stdin);
UserInputHome:
    std::getline(std::cin, userInput);
    if (userInput.empty()) {
        exit(0);
    }
    else {
        if (userInput.length() > 1) {
            std::cout << "Invalid response! Input again: ";
            goto UserInputHome;
        }
        else {
            option = userInput[0];
            switch (option) {
            case '1':
                componentPage();
                break;
            case '2':
                checkoutPage();
                break;
            default:
                std::cout << "Invalid response! Input again: ";
                goto UserInputHome;
            }
        }
    }
}

void componentPage() {
    char option;
    std::string userInput;
    title();
    std::cout << std::endl;
    std::cout << "Select your components (Chronologically recommended)" << std::endl;
    std::cout << std::endl;
    std::cout << "Core components:" << std::endl;
    std::cout << "1. CPU" << std::endl;
    std::cout << "2. Motherboard" << std::endl;
    std::cout << "3. Ram" << std::endl;
    std::cout << "4. SSD" << std::endl;
    std::cout << std::endl;
    customerConfig.shortDisplay();
    std::cout << std::endl;
    std::cout << "Input: ";
    fflush(stdin);
UserInputComp:
    std::getline(std::cin, userInput);
    if (userInput.empty()) {
        homePage();
    }
    else {
        if (userInput.length() > 1) {
            std::cout << "Invalid response! Input again: ";
            goto UserInputComp;
        }
        else {
            option = userInput[0];
            switch (option) {
            case '1':
                cpuPage();
                break;
            case '2':
                motherboardPage();
                break;
            case '3':
                ramPage();
                break;
            case '4':
                ssdPage();
                break;
            default:
                std::cout << "Invalid response! Input again: ";
                goto UserInputComp;
            }
        }
    }
}

void checkoutPage() {
    char yn;
    std::string userInput, coupon;
    totalPrice = calculateTotalCost(customerConfig);
    title();
    if (customerConfig.getCPUIsSelected() == false && customerConfig.getMotherbardIsSelected() == false 
    && customerConfig.getNumRAMs() == 0 && customerConfig.getNumSSDs() == 0) {
        std::cout << "No Component Selected!" << std::endl;
        std::cout << "Press Enter to  go back." << std::endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty() || !userInput.empty()) {
            homePage();
        }
    }
    else {
        std::cout << "Your Cart:" << std::endl;
        customerConfig.display();
        std::cout << std::endl;
        std::cout << "Total Cost: " << totalPrice << " BDT" << std::endl;
        std::cout << std::endl;
        std::cout << "Do you want to confirm your purchase order?(Y/y for yes and you can't go back): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            char yn;
            std::cout << "Do you have any coupon code(Y/y for yes): ";
            std::cin >> yn;
            if (yn == 'y' || yn == 'Y') {
            enterCoupon:
                std::cout << "Enter code: ";
                std::cin >> coupon;
                if (coupon == "Dc2005") {
                    discount = 5;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2010") {
                    discount = 10;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2020") {
                    discount = 20;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else if (coupon == "Dc2030") {
                    discount = 40;
                    calculateDiscountedPrice();
                    goto purchaseComplete;
                }
                else {
                    std::cout << "Invalid code! Want to try again?(Y/y for yes): ";
                    std::cin >> yn;
                    if (yn == 'y' || yn == 'Y') {
                        goto enterCoupon;
                    }
                    else {
                        std::cout << "Completing purchase without discount." << std::endl;
                        goto purchaseComplete;
                    }
                }
            }
            else {
            purchaseComplete:
                generateLog(customerConfig);
                std::cout << "Purchase complete. Press Enter to exit." << std::endl;
                fflush(stdin);
                std::getline(std::cin, userInput);
                if (userInput.empty() || !userInput.empty()) {
                    exit(0);
                }
            }
        }
        else {
            homePage();
        }
    }
}

void cpuPage() {
    int CPUIndex;
    std::string userInput;
    title();
    std::cout << "Select your desired CPU" << std::endl;
    std::cout << std::endl;
    for (i = 0; i < cpuInRep; i++) {
        std::cout << i + 1 << ".\n";
        cpuRepository[i].showInfo();
    }
    std::cout << std::endl;
    if (!(std::cin >> CPUIndex) || CPUIndex < 1 || CPUIndex > cpuInRep) {
        std::cout << "Invalid response!" << std::endl;
    }
    else {
        customerConfig.addCPU(cpuRepository[CPUIndex - 1]);
        std::cout << "Press Enter to continue." << std::endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty()) {
            componentPage();
        }
    }
}

void motherboardPage() {
    int motherboardIndex;
    std::string userInput;
    title();
    std::cout << "Select your desired Motherboard" << std::endl;
    std::cout << std::endl;
    for (i = 0; i < motherboardInRep; i++) {
        std::cout << i + 1 << ".\n";
        motherboardRepository[i].showInfo();
    }
    std::cout << std::endl;
    if (!(std::cin >> motherboardIndex) || motherboardIndex < 1 || motherboardIndex > motherboardInRep) {
        std::cout << "Invalid response!" << std::endl;
    }
    else {
        customerConfig.addMotherboard(motherboardRepository[motherboardIndex - 1]);
        std::cout << "Press Enter to continue." << std::endl;
        fflush(stdin);
        std::getline(std::cin, userInput);
        if (userInput.empty()) {
            componentPage();
        }
    }
}

void ramPage() {
    int ramIndex, quantity;
    char yn;
    title();
    std::cout << "Select your desired RAM" << std::endl;
    std::cout << std::endl;
    for (i = 0; i < ramInRep; i++) {
        std::cout << i + 1 << ".\n";
        ramRepository[i].showInfo();
    }
    std::cout << std::endl;
selectRAM:
    std::cout << "Select: ";
    if (!(std::cin >> ramIndex) || ramIndex < 1 || ramIndex > ramInRep) {
        std::cout << "Invalid response!" << std::endl;
    }
    else {
        std::cout << "Quantity: ";
        std::cin >> quantity;
        customerConfig.addRAM(ramRepository[ramIndex - 1], quantity);
        std::cout << "Do you want to select more (Y/y for yes): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            goto selectRAM;
        }
        else {
            componentPage();
        }
    }
}

void ssdPage() {
    int ssdIndex, quantity;
    char yn;
    title();
    std::cout << "Select your desired SSD" << std::endl;
    std::cout << std::endl;
    for (i = 0; i < ssdInRep; i++) {
        std::cout << i + 1 << ".\n";
        ssdRepository[i].showInfo();
    }
    std::cout << std::endl;
selectSSD:
    std::cout << "Select: ";
    if (!(std::cin >> ssdIndex) || ssdIndex < 1 || ssdIndex > ssdInRep) {
        std::cout << "Invalid response!" << std::endl;
    }
    else {
        std::cout << "Quantity: ";
        std::cin >> quantity;
        customerConfig.addSSD(ssdRepository[ssdIndex - 1], quantity);
        std::cout << "Do you want to select more (Y/y for yes): ";
        std::cin >> yn;
        if (yn == 'y' || yn == 'Y') {
            goto selectSSD;
        }
        else {
            componentPage();
        }
    }
}

double calculateTotalCost(PCConfig config) {
    double totalCost = 0.0;
    totalCost = config.selectedCPU.getPrice() + config.selectedMotherboard.getPrice();
    for (int i = 0; i < config.numRAMs; ++i) {
        totalCost += config.selectedRAM[i].getPrice();
    }
    for (i = 0; i < config.numSSDs; ++i) {
        totalCost += config.selectedSSD[i].getPrice();
    }
    return totalCost;
}

double calculateDiscountedPrice() {
    double discountedPrice;
    discountedPrice = totalPrice - totalPrice * discount / 100;
    return discountedPrice;
}

void generateLog(PCConfig config) {
    time_t now = time(0);
    char *dt = ctime(&now);
    std::ofstream logFile("Private/purchase_log.txt", std::ios::app);
    if (!logFile) {
        std::cerr << "Error creating the log file.\n";
        return;
    }
    logFile << "Time: " << dt;
    logFile << "CPU: " << config.selectedCPU.getName() << " - " << config.selectedCPU.getPrice() << " BDT" << std::endl;
    logFile << "Motherboard: " << config.selectedMotherboard.getName() << " - " << config.selectedMotherboard.getPrice() << " BDT" << std::endl;
    logFile << "RAM:" << std::endl;
    for (i = 0; i < config.numRAMs; ++i) {
        logFile << "- " << config.selectedRAM[i].getName() << "- " << config.selectedRAM[i].getPrice() << " BDT" << std::endl;
    }
    logFile << "SSD:" << std::endl;
    for (i = 0; i < config.numSSDs; ++i) {
        logFile << "- " << config.selectedSSD[i].getName() << "- " << config.selectedSSD[i].getPrice() << " BDT" << std::endl;
    }
    logFile << "Total price: " << totalPrice << " BDT" << std::endl;
    logFile << "Discounted price: " << calculateDiscountedPrice() << std::endl;
    logFile << std::endl;
    logFile.close();
}