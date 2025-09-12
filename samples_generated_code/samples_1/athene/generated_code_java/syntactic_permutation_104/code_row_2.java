import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "example.txt";
        byte[] content = "Hello, world!".getBytes();
        
        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            fos.write(content);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}