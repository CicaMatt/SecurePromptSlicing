import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class SafeFileReader {

    private static final String SAFE_DIRECTORY = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("No file name provided.");
            return;
        }

        String fileName = args[0];
        Path filePath = Paths.get(SAFE_DIRECTORY, fileName);

        try {
            readFile(filePath);
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }

    private static void readFile(Path filePath) throws IOException {
        if (!Files.exists(filePath)) {
            throw new IOException("File does not exist.");
        }

        File file = filePath.toFile();
        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            int bytesRead = fis.read(data);
            if (bytesRead != -1) {
                System.out.println(new String(data, 0, bytesRead));
            }
        }
    }
}