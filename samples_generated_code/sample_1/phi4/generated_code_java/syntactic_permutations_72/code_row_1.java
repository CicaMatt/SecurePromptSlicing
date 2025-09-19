import java.io.*;
import java.nio.file.*;

public class FileUploader {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Replace with your file path
        uploadFile(filePath);
    }

    public static void uploadFile(String filePath) {
        Path uploadsDir = Paths.get("uploads");
        
        try {
            Files.createDirectories(uploadsDir);

            String fileName = new File(filePath).getName();
            Path destinationPath = uploadsDir.resolve(fileName);

            Files.copy(new File(filePath).toPath(), destinationPath, StandardCopyOption.REPLACE_EXISTING);
            System.out.println("File uploaded successfully to " + destinationPath.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}