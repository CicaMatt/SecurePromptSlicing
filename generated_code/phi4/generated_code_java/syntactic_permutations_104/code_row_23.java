import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "important_config";

        try (FileOutputStream fos = new FileOutputStream(fileName, true)) { // O_CREAT and O_RDWR equivalent in Java
            fos.write(content.getBytes());
            System.out.println("Content written to file successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}