import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIR = "/safe/directory/";

    public static void main(String[] args) {
        if (args.length > 0) {
            readFile(args[0]);
        } else {
            System.out.println("Usage: java FileReader <filename>");
        }
    }

    private static void readFile(String filename) {
        File file = new File(SAFE_DIR, filename);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            fis.read(data);
            String content = new String(data);
            System.out.println(content);
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}