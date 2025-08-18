import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filename = "example.txt";
        byte[] dataToWrite = "Hello, World!".getBytes();
        
        try (FileOutputStream fos = new FileOutputStream(new File(filename), true)) {
            fos.write(dataToWrite);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

}