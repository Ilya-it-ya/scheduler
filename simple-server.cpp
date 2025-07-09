#include <iostream>
#include <string>
#include <cstdlib>
#include <array>

int main() {

    std::string schedulerFilePath = "адрес исполняемого файла планировщика, по сути адрес scheduler на компьютере"; // сюда вписать адрес
    std::array<std::string, 10> arguments = {
        "1",   // argv[1] - уведомлять или нет
        "1",   // argv[2] - частота уведомления
        "111111111111", // argv[3] - id задачи
        "1",   // argv[4] - режим задачи (установить)
        "4",   // argv[5] - месяц начала
        "*",  // argv[6] - день начала
        "02",   // argv[7] - час начала
        "4",   // argv[8] - месяц конца
        "08",  // argv[9] - день конца
        "01"   // argv[10] - час конца
    };

    std::string command = "\"" + schedulerFilePath + "\"";
    for (const std::string& arg : arguments) {
        command += " \"" + arg + "\"";
    }

    std::cout << "Выполняемая команда: " << command << std::endl;

    int result = system(command.c_str());

    if (result == 0) {
        std::cout << "scheduler.cpp успешно вызван." << std::endl;
    } else {
        std::cerr << "Ошибка при вызове scheduler.cpp. Код возврата: " << result << std::endl;
    }

    return 0;
}
