#include <fcntl.h>
#include <unistd.h>
int main()
{
	char *arquivo = "LeitorArquivosSysCall/texto.txt";
	char buff[1024];
	int fd;
	int bytes;
	
	fd = open(arquivo , 0);
	bytes = read(fd, buff , 1024);
	if (bytes > 0){
		write(1,buff,bytes);}
	close(fd);
	return 0;
}
