import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class SafeDirectoryReader {
    private static final String SAFE_DIRECTORY_PATH = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeDirectoryReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIRECTORY_PATH, filename);

        if (!file.exists() || !file.isFile()) {
            System.out.println("File does not exist or is not a valid file.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                // Print each byte as character
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}