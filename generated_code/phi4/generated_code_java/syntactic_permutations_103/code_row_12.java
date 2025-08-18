import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            openFile(filePath);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void openFile(String filePath) throws IOException {
        Path path = Paths.get(filePath);

        // Check if file exists
        boolean fileExists = Files.exists(path);

        // O_CREAT and O_EXCL equivalent in Java
        if (!fileExists || !Files.isWritable(path)) {
            // Create a new empty file, fail if it already exists
            Files.createFile(path);
        } else {
            // Truncate the existing file to 0 bytes (O_TRUNC)
            Files.newOutputStream(path).close();
        }

        // Open for writing only (O_WRONLY equivalent in Java is handled by using OutputStream)
    }
}