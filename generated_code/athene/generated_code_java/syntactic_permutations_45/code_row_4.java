import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIRECTORY = "safe_directory_path_here";

    public static void main(String[] args) {
        if (args.length > 0) {
            readFileFromSafeDirectory(args[0]);
        } else {
            System.out.println("Usage: java FileReader <filename>");
        }
    }

    private static void readFileFromSafeDirectory(String filename) {
        File file = new File(SAFE_DIRECTORY, filename);
        try (FileInputStream fis = new FileInputStream(file)) {
            int content;
            while ((content = fis.read()) != -1) {
                System.out.print((char) content);
            }
        } catch (IOException e) {
            System.err.println("Error reading file: " + e.getMessage());
        }
    }
}