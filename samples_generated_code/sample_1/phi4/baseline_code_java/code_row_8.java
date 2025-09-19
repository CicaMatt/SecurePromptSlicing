import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;

public class FileReaderFromSafeDirectory {

    public static void main(String[] args) {
        String safeDirectoryPath = "path/to/safe/directory";
        String fileName = "requestedFile.txt"; // Replace with the actual file name

        readFileFromSafeDirectory(safeDirectoryPath, fileName);
    }

    private static void readFileFromSafeDirectory(String directoryPath, String fileName) {
        File file = new File(directoryPath, fileName);

        if (!file.exists()) {
            System.out.println("File does not exist: " + file.getAbsolutePath());
            return;
        }

        try (FileInputStream fis = new FileInputStream(file)) {
            byte[] buffer = new byte[1024];
            int bytesRead;

            while ((bytesRead = fis.read(buffer)) != -1) {
                String content = new String(buffer, 0, bytesRead);
                System.out.println(content);
            }
        } catch (IOException e) {
            System.err.println("Error reading the file: " + e.getMessage());
        }
    }
}