import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileUploader {

    public static void main(String[] args) {
        String directory = "uploads";
        String filename = "example.txt"; // Replace with the actual file name

        try {
            Path sourceFile = Paths.get("path/to/your/source/file/example.txt"); // Replace with the actual path to your source file
            uploadFile(sourceFile, directory, filename);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public static void uploadFile(Path sourceFilePath, String directoryName, String fileName) throws IOException {
        Path destinationDirectory = Paths.get(directoryName);

        // Create the directory if it does not exist
        if (!Files.exists(destinationDirectory)) {
            Files.createDirectories(destinationDirectory);
        }

        Path destinationPath = destinationDirectory.resolve(fileName);

        // Copy the file to the specified directory
        Files.copy(sourceFilePath, destinationPath, java.nio.file.StandardCopyOption.REPLACE_EXISTING);

        System.out.println("File uploaded successfully: " + destinationPath.toString());
    }
}