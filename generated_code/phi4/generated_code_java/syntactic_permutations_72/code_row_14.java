import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filename = "example.txt"; // Replace with your file name
        uploadFile(filename);
    }

    public static void uploadFile(String filename) {
        Path uploadsDir = Paths.get("uploads");
        
        try {
            Files.createDirectories(uploadsDir);
            Path sourceFilePath = Paths.get(filename); // Assuming the file is in current directory

            if (Files.exists(sourceFilePath)) {
                Path destinationPath = uploadsDir.resolve(filename);
                Files.copy(sourceFilePath, destinationPath, java.nio.file.StandardCopyOption.REPLACE_EXISTING);
                System.out.println("File uploaded successfully to: " + destinationPath.toString());
            } else {
                System.err.println("File does not exist: " + sourceFilePath.toString());
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}