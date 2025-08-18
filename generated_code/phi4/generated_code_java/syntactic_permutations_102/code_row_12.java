import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class ConfigFileHandler {

    public static void main(String[] args) {
        String filePath = "important_config";
        String contentToWrite = "important_config";

        try {
            Path path = Paths.get(filePath);

            // Open the file for reading and writing. If it doesn't exist, create it.
            Files.write(path, contentToWrite.getBytes(), 
                        StandardOpenOption.CREATE, 
                        StandardOpenOption.WRITE, 
                        StandardOpenOption.READ);
            
            System.out.println("File written successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}