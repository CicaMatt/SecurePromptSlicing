import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;

public class SafeFileReader {

    public static void main(String[] args) {
        String safeDirectoryPath = "path/to/safe/directory";
        String fileName = "requested_file.txt";

        String filePath = Paths.get(safeDirectoryPath, fileName).toString();

        try (FileInputStream fis = new FileInputStream(new File(filePath))) {
            byte[] data = new byte[(int) new File(filePath).length()];
            int bytesRead = fis.read(data);
            
            if (bytesRead != -1) {
                System.out.println("File content: " + new String(data));
            } else {
                System.out.println("Failed to read file.");
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}
