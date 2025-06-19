import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.channels.FileChannel;

public class FileManager {
    public static void main(String[] args) throws IOException {
        
        //open a file for reading and writing
        FileDescriptor fd = open("file.txt", O_RDWR | O_CREAT);
       
        //write some bytes to the file using write()
        FileOutputStream fos = new FileOutputStream(fd);
        
        String data = "Hello World!";
        fos.write(data.getBytes());
        fos.close();
    }
}