import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createIfNotExists = true;
        boolean truncateIfExists = true;
        boolean writeOnly = true;
        boolean failIfExists = true;

        try {
            open(filePath, createIfNotExists, truncateIfExists, writeOnly, failIfExists);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static void open(String filePath, boolean O_CREAT, boolean O_TRUNC, boolean O_WRONLY, boolean O_EXCL) throws IOException {
        File file = new File(filePath);

        if (O_EXCL && file.exists()) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (!file.exists() && O_CREAT) {
            if (!file.createNewFile()) {
                throw new IOException("Failed to create the file.");
            }
        } else if (file.exists() && O_TRUNC) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Truncating by opening in write mode with false append
            }
        }

        if (!O_WRONLY) {
            throw new IOException("Only write operations are allowed.");
        }

        System.out.println("File opened successfully.");
    }
}