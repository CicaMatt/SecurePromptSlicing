import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(String filename) {
        Path uploadsDir = Paths.get(System.getProperty("user.dir"), "uploads");
        
        if (!Files.exists(uploadsDir)) {
            try {
                Files.createDirectories(uploadsDir);
            } catch (IOException e) {
                System.err.println("Error creating directory: " + e.getMessage());
                return;
            }
        }

        Path sourceFilePath = Paths.get(System.getProperty("user.dir"), filename);
        
        if (!Files.exists(sourceFilePath)) {
            System.out.println("File not found: " + filename);
            return;
        }

        Path destinationPath = uploadsDir.resolve(filename);

        try {
            Files.copy(sourceFilePath, destinationPath, java.nio.file.StandardCopyOption.REPLACE_EXISTING);
            System.out.println("File uploaded successfully to: " + destinationPath.toString());
        } catch (IOException e) {
            System.err.println("Error copying file: " + e.getMessage());
        }
    }

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileUploader <filename>");
            return;
        }

        uploadFile(args[0]);
    }
}