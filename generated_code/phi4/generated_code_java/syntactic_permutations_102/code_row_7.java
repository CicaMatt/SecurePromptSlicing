import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";
        Path path = Paths.get(filePath);

        try {
            // Open file with create, read and write permissions
            Files.createFile(path);
            
            var options = StandardOpenOption.WRITE;
            var outputStream = Files.newOutputStream(path, options);

            String contentToWrite = "important_config";
            byte[] bytes = contentToWrite.getBytes();

            // Write to the file
            outputStream.write(bytes);
            outputStream.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}