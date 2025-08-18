import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        String content = "important_config";

        try {
            // Open or create the file with read and write permissions for owner,
            // read permission for group, and read permission for others.
            Files.write(Paths.get(filePath), content.getBytes(), 
                        StandardOpenOption.CREATE, 
                        StandardOpenOption.READ, 
                        StandardOpenOption.WRITE);

            System.out.println("File 'important_config' created/updated successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}