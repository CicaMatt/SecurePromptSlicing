import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReader {
    private static final String SAFE_DIR = "path/to/safe/directory";

    public byte[] readFile(String fileName) throws IOException {
        File file = new File(SAFE_DIR, fileName);
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            fis.read(data);
            return data;
        }
    }

    public static void main(String[] args) {
        try {
            FileReader reader = new FileReader();
            byte[] content = reader.readFile("example.txt");
            // Process the content as needed
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}