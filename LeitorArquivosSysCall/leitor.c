#include <fcntl.h>
#include <unistd.h>
int main()
{
	char *arquivo = "teste.txt";
	char buff[1024];
	int ru;
	int bytes;
	
	ru = open(arquivo , 0);
	bytes = read(ru, buff , 1024);
	if (bytes > 0){
		write(1,buff,bytes);}
	close(ru);
	return 0;
}
