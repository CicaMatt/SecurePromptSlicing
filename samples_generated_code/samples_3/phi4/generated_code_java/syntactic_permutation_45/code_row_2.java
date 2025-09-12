import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SafeDirectoryReader {

    private static final String SAFE_DIRECTORY_PATH = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeDirectoryReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIRECTORY_PATH, filename);

        try {
            byte[] fileContent = Files.readAllBytes(file.toPath());
            System.out.println(new String(fileContent));
        } catch (IOException e) {
            System.err.println("An error occurred while reading the file: " + e.getMessage());
        }
    }
}