import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIR = "/safe/directory/path";

    public static void main(String[] args) {
        if (args.length > 0) {
            String fileName = args[0];
            readFileFromSafeDirectory(fileName);
        } else {
            System.out.println("Please provide a filename as an argument.");
        }
    }

    private static void readFileFromSafeDirectory(String fileName) {
        File file = new File(SAFE_DIR, fileName);
        if (file.exists() && !file.isDirectory()) {
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] content = new byte[(int) file.length()];
                fis.read(content);
                System.out.println(new String(content));
            } catch (IOException e) {
                System.err.println("Error reading the file: " + e.getMessage());
            }
        } else {
            System.out.println("File does not exist or is a directory.");
        }
    }
}