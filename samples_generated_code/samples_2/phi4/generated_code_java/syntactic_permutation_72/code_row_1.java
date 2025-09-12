import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void uploadFile(Path sourceFilePath, String destinationDirectory) throws IOException {
        if (sourceFilePath == null || !Files.exists(sourceFilePath)) {
            throw new IllegalArgumentException("Source file path is invalid or does not exist.");
        }
        
        Path uploadsDir = Paths.get(destinationDirectory);
        if (!Files.exists(uploadsDir)) {
            Files.createDirectories(uploadsDir);
        }

        String fileName = sourceFilePath.getFileName().toString();
        Path destinationPath = uploadsDir.resolve(fileName);

        Files.copy(sourceFilePath, destinationPath);
    }

    public static void main(String[] args) {
        try {
            Path sourceFile = Paths.get("path/to/your/source/file.txt");
            String destinationDirectory = "uploads";
            uploadFile(sourceFile, destinationDirectory);
            System.out.println("File uploaded successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}