import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class FileReaderFromSafeDirectory {

    private static final String SAFE_DIRECTORY = "path/to/safe/directory";

    public static void main(String[] args) {
        if (args.length == 0) {
            System.out.println("Please provide the filename as an argument.");
            return;
        }

        String fileName = args[0];
        File file = new File(SAFE_DIRECTORY, fileName);

        if (!file.exists() || !file.isFile()) {
            System.out.println("File not found in safe directory.");
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] data = new byte[(int) file.length()];
            int bytesRead = fis.read(data);
            
            if (bytesRead != -1) {
                String content = new String(data);
                System.out.println("File Content:\n" + content);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}