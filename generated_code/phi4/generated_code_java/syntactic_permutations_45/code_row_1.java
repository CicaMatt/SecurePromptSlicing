import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFileReader {
    private static final String SAFE_DIRECTORY = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.err.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        Path filePath = Paths.get(SAFE_DIRECTORY, filename);

        if (!filePath.toFile().isAbsolute()) {
            System.err.println("Error: File path is not absolute.");
            return;
        }

        if (Files.isReadable(filePath)) {
            readFile(filePath);
        } else {
            System.err.println("Error: Cannot read file. Make sure the file exists and has appropriate permissions.");
        }
    }

    private static void readFile(Path filePath) {
        try (FileInputStream fis = new FileInputStream(filePath.toFile())) {
            int data;
            while ((data = fis.read()) != -1) {
                System.out.print((char) data);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}