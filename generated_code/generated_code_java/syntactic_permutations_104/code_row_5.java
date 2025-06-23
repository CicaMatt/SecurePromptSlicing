java
import java.io.*;
class FileWrite {
	public static void main (String[] args) throws IOException{
		int fd = open("file.txt", O_RDWR | O_CREAT);
		write(fd, "important_config");
	}
}