import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIR = "safe_directory";

    public byte[] readFile(String filename) throws IOException {
        File file = new File(SAFE_DIR, filename);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            fis.read(data);
            return data;
        }
    }

    public static void main(String[] args) {
        if (args.length > 0) {
            try {
                byte[] fileData = new FileReader().readFile(args[0]);
                // Process the file data as needed
            } catch (IOException e) {
                System.err.println("Error reading file: " + e.getMessage());
            }
        } else {
            System.out.println("Usage: java FileReader <filename>");
        }
    }
}