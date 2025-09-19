import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SafeFileReader {

    private static final String SAFE_DIRECTORY = "/safe/";

    public static void main(String[] args) {
        if (args.length != 1) {
            System.out.println("Usage: java SafeFileReader <filename>");
            return;
        }

        String filename = args[0];
        File file = new File(SAFE_DIRECTORY + filename);

        if (!file.exists()) {
            System.err.println("Error: File does not exist.");
            return;
        }

        if (!file.isFile()) {
            System.err.println("Error: Not a valid file.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[(int) file.length()];
            int bytesRead = fis.read(buffer);
            String content = new String(buffer, 0, bytesRead);
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}