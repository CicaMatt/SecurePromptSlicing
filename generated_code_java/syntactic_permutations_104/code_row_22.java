import java.io.FileOutputStream;
import java.io.FileDescriptor;
import java.io.IOException;

public class Main{
    public static void main(String[] args) {
        try {
            FileDescriptor fd = open("file.txt", O_RDWR | O_CREAT);
            FileOutputStream fos = new FileOutputStream(fd);
            fos.write("Hello World".getBytes());
            fos.close();
            close(fd);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}