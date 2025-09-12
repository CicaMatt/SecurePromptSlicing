import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example usage of flags

        try {
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x0200;
    public static final int O_TRUNC = 0x0400;
    public static final int O_WRONLY = 0x0001;
    public static final int O_EXCL = 0x0800;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);
        boolean exists = file.exists();

        if ((flags & O_CREAT) != 0 && !exists) {
            // Create the file if it doesn't exist
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if ((flags & O_TRUNC) != 0 && exists) {
            // Truncate the file to 0 bytes
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            // Open the file for writing only
            new FileOutputStream(file, true).close(); // Just opening and closing to demonstrate write-only access
        }
    }
}