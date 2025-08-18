import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            // O_CREAT | O_TRUNC | O_WRONLY | O_EXCL equivalent in Java
            FileOutputStream fos = new FileOutputStream(filePath, false);
            // Writing to the file
            fos.write("Hello, World!".getBytes());
            fos.close();
        } catch (IOException e) {
            System.err.println("Error opening or writing to the file: " + e.getMessage());
        }
    }
}