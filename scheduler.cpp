#include <iostream>
#include <string>
#include <cstdlib> 
#include <vector>
#include <iterator>
using namespace std;

void createCronTask(
    string executablePath, // путь к исполняемому файлу
    string minute,       // минута (например "*/5")
    string hour,         // час (например "*")
    string dayOfMonth,   // день месяца (например "1,15")
    string month,        // месяц (например "1-6")
    string dayOfWeek,    // день недели (например "0,6")
    string arg1 ,                  // первый аргумент (простое значение)
    string arg2                    // второй аргумент (простое значение)
) {

    string cronCommand = "(crontab -l 2>/dev/null; echo \"";


    cronCommand += minute + " ";
    cronCommand += hour + " ";
    cronCommand += dayOfMonth + " ";
    cronCommand += month + " ";
    cronCommand += dayOfWeek + " ";


    cronCommand += "\\\"" + executablePath + "\\\" ";
    cronCommand += arg1 + " " + arg2;


    cronCommand += "\") | crontab -";

    int result = system(cronCommand.c_str());

    if (result == 0) {
       cout << "Cron-задача успешно создана!" << endl;
        cout << "Команда: " << cronCommand << endl;
    } else {
       cerr << "Ошибка при создании cron-задачи!" << endl;
    }
}

void remove_cron_by_exact_match(string search_str) {
    string cmd = "crontab -l | grep -v \"" + search_str + "\" | crontab -";
    

    int result = system(cmd.c_str());
    
    if (result == 0) {
        cout << "Задача, содержащая '" << search_str << "', удалена.\n";
    } else {
        cerr << "Ошибка при удалении cron-задачи.\n";
    }
}

int main(int argc, char* argv[]){ //argv[имя, уведомлять или нет, частота уведомления где 1 - раз в день по будням в 10 часов, id задачи, режим задачи где 1 - установить задачу 2 - удалить задачу, месяц н, день н, час н, месяц к, день к, час к]
    
    string locate_server_cpp = "путь"; //путь к серверному файлу или заглушке simple-server, инициализирующему уведомления
    string locate_scheduler_cpp = "путь"; //путь к этому файлу
    string locate_notification_cpp = "путь"; //путь к файлу, инициализирующему уведомление для отправки пользовател (notification), или любому другому файлу, который должен вызвваться с помощью cron.


    
    if(argc==11)
    {
    string argv3 = argv[3];
    string argv5 = argv[5];
    string argv6 = argv[6];
    string argv7 = argv[7];
    string argv8 = argv[8];
    string argv9 = argv[9];
    string argv10 = argv[10];
    
    //createCronTask(locate_server_cpp, "*", "10", "10", "10","1-5", "15");
    //if (string(argv[1])=="1"){ уведмолять или нет 
           //  if (string(argv[2])=="1"){ //частота уведомлений, по умолчанию  режим - 1 (раз в день)
            if (string(argv[4])=="1"){  //режим задачи (удалить существующую по айдишнику - 0, добавить задачу - 1)
                createCronTask(locate_scheduler_cpp, "02", "02", argv6, argv5 ,"1-5", argv3, argv[4] ); 
                
                createCronTask(locate_scheduler_cpp, "04", "02", argv9, argv8,"*", argv3, "" );


              } 
            if (string(argv[4])=="0"){
                remove_cron_by_exact_match(argv[3]);
            }

            //}
        //}

    }
    if(argc==2){ //argv[имя, id задачи для удаления]
        remove_cron_by_exact_match(argv[1]);
    }
    if(argc == 3){ //argv[имя, id задачи, режим уведомления (пока по умолчанию 1 - раз в день в 10 часов)]
        //if (string(argv[2])=="1")
        {
        createCronTask(locate_notification_cpp, "00", "10", "*", "*","1-5", argv[1], "");
        }
    }
    
    
    return 0;
}