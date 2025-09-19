import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(byte[] fileData, String filename) throws IOException {
        String uploadsDirectory = "uploads";
        Path directoryPath = Paths.get(uploadsDirectory);

        if (!Files.exists(directoryPath)) {
            Files.createDirectories(directoryPath);
        }

        Path filePath = directoryPath.resolve(filename);
        Files.write(filePath, fileData);
    }

    public static void main(String[] args) {
        try {
            // Example usage
            byte[] exampleFileData = "Example file content".getBytes();
            String exampleFilename = "example.txt";
            uploadFile(exampleFileData, exampleFilename);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}