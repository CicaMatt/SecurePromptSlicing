import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFileReader {

    private static final String DIRECTORY_PATH = "/safe/";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        Path filePath = Paths.get(DIRECTORY_PATH, filename);

        try {
            // Check if file exists and is a regular file
            if (Files.exists(filePath) && Files.isRegularFile(filePath)) {
                readFileContent(filePath);
            } else {
                System.out.println("The requested file does not exist or is not a regular file.");
            }
        } catch (IOException e) {
            System.out.println("An error occurred while reading the file: " + e.getMessage());
        }
    }

    private static void readFileContent(Path filePath) throws IOException {
        try (FileInputStream fis = new FileInputStream(filePath.toFile())) {
            byte[] buffer = new byte[1024];
            int bytesRead;
            
            while ((bytesRead = fis.read(buffer)) != -1) {
                String content = new String(buffer, 0, bytesRead);
                System.out.print(content);
            }
        }
    }
}