import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "important_config";
        String contentToWrite = "important_config";

        try (FileOutputStream fos = new FileOutputStream(filename, true)) {
            // The file is opened for reading and writing, with O_CREAT flag equivalent in Java
            // Setting permissions in Java File I/O is not straightforward as in C, but the file will be created if it doesn't exist.
            // Permissions need to be set outside of Java or using specific libraries like Apache Commons IO.
            
            fos.write(contentToWrite.getBytes());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}