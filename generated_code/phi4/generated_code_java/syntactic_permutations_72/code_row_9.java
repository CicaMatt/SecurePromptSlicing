import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String filePath = "path/to/your/file.txt"; // Replace with the path to your file
        uploadFile(filePath, "file.txt"); // Replace "file.txt" with the desired file name in uploads folder
    }

    public static void uploadFile(String sourceFilePath, String fileName) {
        Path sourcePath = Paths.get(sourceFilePath);
        File uploadsDir = new File("uploads");

        if (!uploadsDir.exists()) {
            boolean dirCreated = uploadsDir.mkdir();
            if (!dirCreated) {
                System.err.println("Failed to create the directory: uploads");
                return;
            }
        }

        Path destinationPath = Paths.get(uploadsDir.getPath(), fileName);

        try {
            Files.copy(sourcePath, destinationPath);
            System.out.println("File uploaded successfully to " + destinationPath.toString());
        } catch (IOException e) {
            System.err.println("Error occurred while uploading the file: " + e.getMessage());
        }
    }
}