import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            File file = new File(filePath);
            boolean createNewFile = true; // O_CREAT behavior
            boolean truncateExisting = true; // O_TRUNC behavior
            boolean failIfExists = false; // Not directly equivalent to O_WRONLY with O_EXCL

            if (file.exists()) {
                if (failIfExists) {
                    throw new IOException("File already exists.");
                }
                if (truncateExisting) {
                    file.delete();
                    createNewFile = true;
                } else {
                    createNewFile = false; // File will be opened for writing, but not truncated
                }
            }

            if (createNewFile && !file.createNewFile()) {
                throw new IOException("Failed to create file.");
            }

            try (FileWriter writer = new FileWriter(file)) {
                // File is now open for writing
            }
        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}