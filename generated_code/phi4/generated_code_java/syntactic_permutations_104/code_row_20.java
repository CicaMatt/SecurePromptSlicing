import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config.txt";
        String content = "important_config";

        try {
            Path path = Paths.get(fileName);
            boolean fileExists = Files.exists(path);

            FileOutputStream fos = new FileOutputStream(fileName, !fileExists); // O_RDWR + O_CREAT
            fos.write(content.getBytes());
            fos.close();
            
            System.out.println("File written successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}