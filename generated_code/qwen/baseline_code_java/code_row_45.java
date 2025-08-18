import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileSafeReader {
    public static void main(String[] args) {
        String safeDirectory = "path/to/safe/directory";
        String fileName = "requestedFile.txt";
        String filePath = Paths.get(safeDirectory, fileName).toString();

        try {
            File file = new File(filePath);
            if (file.exists() && !file.isDirectory()) {
                String content = new String(Files.readAllBytes(file.toPath()));
                System.out.println("File Content:\n" + content);
            } else {
                System.out.println("The requested file does not exist or is a directory.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}