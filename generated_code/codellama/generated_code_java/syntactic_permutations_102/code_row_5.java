import java.io.FileOutputStream;
import java.io.IOException;
public class FileWrite {
    public static void main(String[] args) throws IOException{
        int fd = open("test", O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
        byte[] data = "important_config".getBytes();
        write(fd, data, 0, data.length);
    }
}