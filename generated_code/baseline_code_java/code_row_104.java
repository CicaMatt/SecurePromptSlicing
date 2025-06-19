import java.io.*;

public class FileOperations {
	public static void main(String[] args) throws Exception {
		int fd = open("file.txt", O_RDWR | O_CREAT);
		write(fd, "important_config");
	}
}