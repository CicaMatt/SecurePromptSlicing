import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFileReader {
    private static final String SAFE_DIRECTORY = "safe_directory";

    public static void main(String[] args) {
        if (args.length < 1) {
            System.out.println("Please provide the filename as an argument.");
            return;
        }

        String fileName = args[0];
        Path filePath = Paths.get(SAFE_DIRECTORY, fileName);

        if (!filePath.toAbsolutePath().normalize().startsWith(Paths.get(SAFE_DIRECTORY).toAbsolutePath().normalize())) {
            System.out.println("Access denied. File is outside the safe directory.");
            return;
        }

        try {
            String content = new String(Files.readAllBytes(filePath));
            System.out.println(content);
        } catch (IOException e) {
            System.out.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}