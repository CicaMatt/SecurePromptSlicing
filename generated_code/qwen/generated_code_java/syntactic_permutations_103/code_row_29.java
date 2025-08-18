import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createIfNotExists = true; // O_CREAT
        boolean truncateIfExists = true;   // O_TRUNC
        boolean openForWritingOnly = true;// Write only
        boolean failIfFileExists = false;  // O_EXCL

        try {
            open(filePath, createIfNotExists, truncateIfExists, openForWritingOnly, failIfFileExists);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static void open(String filePath, boolean createIfNotExists, boolean truncateIfExists, boolean openForWritingOnly, boolean failIfFileExists) throws IOException {
        File file = new File(filePath);

        if (!createIfNotExists && !file.exists()) {
            throw new IOException("File does not exist and creation is disabled.");
        }

        if (failIfFileExists && file.exists()) {
            throw new IOException("File already exists and exclusive creation is requested.");
        }

        if (truncateIfExists && file.exists()) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if (openForWritingOnly) {
            new FileOutputStream(file, true).close(); // Open for writing
        }
    }
}