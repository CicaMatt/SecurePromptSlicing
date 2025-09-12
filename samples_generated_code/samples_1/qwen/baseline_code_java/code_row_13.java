import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example usage of flags

        try {
            open(fileName, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static final int O_RDONLY = 0x000;
    public static final int O_WRONLY = 0x001;
    public static final int O_RDWR = 0x002;
    public static final int O_CREAT = 0x200;
    public static final int O_EXCL = 0x800;
    public static final int O_TRUNC = 0x400;

    public static void open(String fileName, int flags) throws IOException {
        File file = new File(fileName);
        boolean exists = file.exists();

        if ((flags & O_CREAT) == 0 && !exists) {
            throw new IOException("File does not exist and O_CREAT flag is not set.");
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (exists && (flags & O_TRUNC) != 0) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close(); // Open for writing
        }
    }
}