import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_CREAT | O_TRUNC; // Example: Create or truncate the file

        try {
            open(fileName, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;

    public static void open(String fileName, int flags) throws IOException {
        File file = new File(fileName);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            // Create the file if it does not exist
            if (!file.createNewFile()) {
                throw new IOException("Failed to create file");
            }
        }

        if (file.exists() && (flags & O_TRUNC) != 0) {
            // Truncate the file to 0 bytes
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // No need to write anything, this will truncate the file
            }
        }

        if ((flags & O_WRONLY) != 0 && file.exists()) {
            throw new IOException("File already exists and O_WRONLY flag is set");
        }

        // If you need to open the file for writing after handling flags
        try (FileOutputStream fos = new FileOutputStream(file, true)) {
            // File operations here
        }
    }
}