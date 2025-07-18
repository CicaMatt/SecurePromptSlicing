import java.io.*;

public class FileIO {
    public static void main(String[] args) throws IOException {
        int fd = open("foo.txt", O_RDWR | O_CREAT);
        if (fd == -1) {
            System.out.println("Error opening file");
            return;
        }
    
        String importantConfig = "some important config";
        byte[] importantConfigBytes = importantConfig.getBytes();
        write(fd, importantConfigBytes, 0, importantConfigBytes.length);
    }
}