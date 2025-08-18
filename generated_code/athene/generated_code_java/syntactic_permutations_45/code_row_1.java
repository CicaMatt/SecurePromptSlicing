import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class SafeFileReader {
    private static final String SAFE_DIR = "safe_directory/";

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide a filename as an argument.");
            return;
        }
        readFileFromSafeDirectory(args[0]);
    }

    private static void readFileFromSafeDirectory(String fileName) {
        File file = new File(SAFE_DIR, fileName);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] content = new byte[fis.available()];
            fis.read(content);
            System.out.println(new String(content));
        } catch (IOException e) {
            System.out.println("Error reading the file: " + e.getMessage());
        }
    }
}