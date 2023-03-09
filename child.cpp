#include <iostream>
#include <filesystem>
#include <sys/types.h>
#include <unistd.h>


using namespace std;
using namespace std::filesystem;

extern char** environ;

 int main(int argc, char* argv[])
{
cout << "Количество переданных параметров равняется: " << argc << endl;
        cout << "Запустилась программа Child" << endl;
	cout << "PID child: " << getpid() << endl;
	cout << "PID parent: " << getppid() << endl;
	cout << "===========================" << endl;
	for(int i = 0; i < argc; ++i)
	{
		cout <<"argv[" << i <<"] = " << argv[i] << endl;
	}
	cout << "===========================" << endl;
	if(environ == nullptr)
	{
		cout << "Environ является нулевым указателем " << endl;
	}
	else 
	{
		cout << "Environ является не неулевым указателем" << endl;
	}	
	for(int i = 0; environ[i] != NULL; i++)
	{
	//cout << "Прошла итерация environ[i]" << endl;
		cout << "Третий параметр ["<< i << "] = " << environ[i] << endl;
	}	
	
	cout << "Завершилась программа Child" << endl;
	
	//
	char ch;
	ch = getchar();    //Удалить 
	//
	exit(123);
}
