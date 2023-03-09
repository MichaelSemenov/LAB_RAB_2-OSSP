//fork() - оздает новый процесс, который является копией родительского процесса
// Этот код демонстрирует использование функции fork() для создания процесса-потомка.
// Функция fork() создает новый процесс, который является копией родительского процесса,
// и возвращает pid нового процесса. Если pid равно 0, то это означает, что это процесс-потомок,
// а если pid > 0, то это значит, что это родительский процесс.
// getpid() возвращает pid текущего процесса.



//execve() - осуществляет вызов функции main, находящейся в другой программе, передавая ей свои аргументы в качестве входных. Заменяем образ текущего процесса другой программой.
//int execve(const char* path, char* const argv[], char* const envp[]) 
	//const char* path - путь программы
	//argv[0] - имя программы; argv[1],[2] и т.д - аргументы передаваемые программой
	//Если execve() произошла ошибка - то return -1;
	



//Если в данную прогу написать fork, то ubuntu сломается


#include <iostream>
#include <filesystem>
#include <sys/types.h>
#include <unistd.h>
#include <string>
#include <string.h>
#include <cstdlib>
#include <sys/wait.h>
#include <clocale>


using namespace std;
using namespace std::filesystem;

extern char** environ;


void show_command()
{
	cout << "============Команды обработки нажатий============" << endl;
	cout << "[+] Запустить программу Child используя getevn().Информацию о каталоге, где размещается child, получает из окружения, используя функцию getenv(). Имя программы (argv[0]) устанавливается как child_XX, где XX ‒ порядковый номер от 00 до 99. Номер инкрементируется родителем." << endl;
	cout << "[*] Как [+], но информацию о расположении программы child получает, сканируя массив параметров среды,переданный в третьем параметре функции main()." << endl;
	cout << "[&] порождает дочерний процесс аналогично предыдущему случаю, однако информацию о расположении программы child получает, сканируя массив параметров среды, указанный во внешней переменной extern char **environ, установленной хост-средой при запуске (см. IEEE Std 1003.1-2017)." << endl;
	cout << "[q] завершение родительского процесса(программы)." << endl;
}



int main(int argc, char* argv[], char* envp[])
{
        for(int i =0; environ[i] != NULL; ++i)
        {
        	cout << "Параметр хост-среды environ[" << i << "] = " << environ[i] << endl;
        }	
//
//        Установка пути программы в хост среду независимо от программы
//
		 
		
	cout << "Сканирование третьего массива с какими-то параметрами" << endl;
	if(envp == nullptr)
	{
		cout << "Данный указатель равен нулю" << endl;
	}
	else 
	{
		cout << "Данный указатель не нулевой" << endl;
	}
	for(int i =0; envp[i] != NULL; ++i)
	{
		cout << "envp[" << i << "] = " << envp[i] << endl;
	}

	cout << "Запустилась программа Parent " << endl;
	cout << "PID родительского процесса: " << getppid() << endl;
	cout << "PID процесса данной программы" << getpid() << endl;
 	show_command();
 	char command;
 	while(command!='q')
 	{ 
 	cout << "Ваша команда: ";
 		cin >> command; 
 		cout << "Проверка работы программы-->>" << endl;
 		switch(command)
 		{
 			case '+':
 			{
		   string temp = "/home/michael/Михалыч(Учеба)/ОСиСП/Лабараторные работы/LAB_RAB_2/child";
 			  char hostname[256];
 			  gethostname(hostname, sizeof(hostname));;
 			  char* LOGNAME = getenv("LOGNAME");
 			  char* test_getenv = getenv("PATH");
 			  char* LANG = getenv("LANG");
 			  char* SHELL = getenv("SHELL");
 			  char* TERM = getenv("TERM");
 			  char* HOME = getenv("HOME"); 
 			  char* USER = getenv("USER");
 			  char* PATH = (char*)(temp.c_str());
 			  char* lc_collate = setlocale(LC_COLLATE, NULL);
 	//cout << "LOCALE: " << setlocale(LC_COLLATE, NULL) <<endl;	  
 	
 	
 	
 	cout << "Параметры до передачи в программу -> " << LOGNAME << test_getenv << LANG << SHELL << TERM << HOME << USER << PATH << lc_collate << endl;
 	
 	
 			  char *argv[] = { PATH ,test_getenv ,  hostname , LOGNAME, LANG, SHELL,TERM , HOME, USER, lc_collate, NULL };
 			  pid_t test = fork();
 			  cout << "Значение процесса после использования fork" << test << endl;
 			  if(test  == 0)
 			  {
 			  	execve( "/home/michael/Михалыч(Учеба)/ОСиСП/Лабараторные работы/LAB_RAB_2/child", argv , NULL); 
       			  }
       			  else 
       			  {
       			  	waitpid(test, NULL, 0);
       			  }
       			  cout << "Проверка вывода значения процесса" << test << endl; 
       			break;
        		}
 			case '*':
 				{
 				char** enviroment = envp;
 				while(*enviroment != NULL)
 				{
 				    if(strncmp(*enviroment, "PATH=",5))
 				    {
 				    	cout << "PATH:" << *enviroment << endl;
 				    	char* path = strtok(*enviroment+5, ":");
 				    	while (path != NULL) {
                // Формируем полный путь к программе child
                char full_path[256];
                sprintf(full_path, "%s/child", path);

                // Проверяем, существует ли файл по указанному пути
                if (access(full_path, F_OK) == 0) {
                    cout << "child found at " << full_path << endl;
                    break;
                }

                path = strtok(NULL, ":");
            }
 				    }
 				    enviroment++;
 				}
 				*enviroment = "/home/michael/Михалыч(Учеба)/ОСиСП/Лабараторные работы/LAB_RAB_2/child" ;
 				break;
 				}
 			case '&':
 			{
 			*environ = "/home/michael/Михалыч(Учеба)/ОСиСП/Лабараторные работы/LAB_RAB_2/child";
		cout << *environ << endl;
 			string temp = "/home/michael/Михалыч(Учеба)/ОСиСП/Лабараторные работы/LAB_RAB_2/child";
 			  char hostname[256];
 			  gethostname(hostname, sizeof(hostname));;
 			  char* LOGNAME = getenv("LOGNAME");
 			  char* test_getenv = getenv("PATH");
 			  char* LANG = getenv("LANG");
 			  char* SHELL = getenv("SHELL");
 			  char* TERM = getenv("TERM");
 			  char* HOME = getenv("HOME"); 
 			  char* USER = getenv("USER");
 			  char* PATH = (char*)(temp.c_str());
 			  char* lc_collate = setlocale(LC_COLLATE, NULL);
 	//cout << "LOCALE: " << setlocale(LC_COLLATE, NULL) <<endl;	  
 			  char *argv[] = { PATH ,test_getenv ,  hostname , LOGNAME, LANG, SHELL,TERM , HOME, USER, lc_collate, NULL };
				pid_t test = fork();
				
			 	if(test == 0) 
			 	{
			 		execve( *environ, argv , NULL);
			 	}
			 	else 
			 	{
			 		waitpid(test, NULL, 0);	
			 	}
 				break;
 				}
 			case 'q':
 				break;
 			default:
 				
 				cerr << "Неверный тип комманды, повторите попытку снова" << endl;			
 				break;
 		}
 	}

	return 0;
}


