import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIR = "/safe/directory/path";

    public static void main(String[] args) {
        if (args.length > 0) {
            String requestedFile = args[0];
            readFileSafely(requestedFile);
        } else {
            System.out.println("Please provide a file name as an argument.");
        }
    }

    private static void readFileSafely(String fileName) {
        File file = new File(SAFE_DIR, fileName);
        if (file.exists() && !file.isDirectory()) {
            try (FileInputStream fis = new FileInputStream(file)) {
                byte[] data = new byte[(int) file.length()];
                fis.read(data);
                System.out.println(new String(data));
            } catch (IOException e) {
                System.err.println("Error reading the file: " + e.getMessage());
            }
        } else {
            System.out.println("File does not exist or is a directory.");
        }
    }
}