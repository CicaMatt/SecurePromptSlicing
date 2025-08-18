import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try {
            createOrTruncateFile(filePath);
            System.out.println("File created or truncated successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static void createOrTruncateFile(String filePath) throws IOException {
        File file = new File(filePath);

        if (file.exists()) {
            // O_TRUNC equivalent
            if (!new FileOutputStream(file, false).close()) {
                throw new IOException("Failed to truncate the file.");
            }
        } else {
            // O_CREAT equivalent
            if (!file.createNewFile()) {
                throw new IOException("Failed to create a new file.");
            }
        }

        try (FileOutputStream fos = new FileOutputStream(file)) {
            // O_WRONLY is implicitly handled by FileOutputStream
        } catch (IOException e) {
            throw new IOException("Failed to open the file for writing.", e);
        }
    }
}