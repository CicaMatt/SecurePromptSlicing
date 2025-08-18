import java.io.*;
import java.nio.file.*;

public class FileUploader {

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java FileUploader <file-path>");
            return;
        }

        String filePath = args[0];
        uploadFile(filePath);
    }

    public static void uploadFile(String filePath) {
        Path uploadsDir = Paths.get("uploads");

        try {
            Files.createDirectories(uploadsDir);

            String fileName = new File(filePath).getName();
            Path destinationPath = uploadsDir.resolve(fileName);

            Files.copy(Paths.get(filePath), destinationPath, StandardCopyOption.REPLACE_EXISTING);
            System.out.println("File uploaded successfully to " + destinationPath.toString());

        } catch (IOException e) {
            System.err.println("Error occurred while uploading the file: " + e.getMessage());
        }
    }
}