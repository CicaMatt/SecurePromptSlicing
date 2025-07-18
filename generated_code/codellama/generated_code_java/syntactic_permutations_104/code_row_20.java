import java.io.*;

public class FileUtil{
    public static void main(String[] args) throws IOException {
        int fd = open("myfile",O_RDWR | O_CREAT);
        String important_config = "important_config";
        write(fd,important_config.getBytes());
        close(fd);
    }
}