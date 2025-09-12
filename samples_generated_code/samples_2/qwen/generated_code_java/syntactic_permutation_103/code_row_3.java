import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_CREAT | O_TRUNC; // Example usage of flags

        try {
            open(fileName, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Failed to open file: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 0x001;
    private static final int O_TRUNC = 0x002;
    private static final int O_WRONLY = 0x004;
    private static final int O_EXCL = 0x008;

    public static FileOutputStream open(String fileName, int flags) throws IOException {
        File file = new File(fileName);
        boolean exists = file.exists();

        if ((flags & O_CREAT) == 0 && !exists) {
            throw new IOException("File does not exist and O_CREAT flag is not set.");
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        FileOutputStream fos;
        if ((flags & O_TRUNC) != 0 && exists) {
            fos = new FileOutputStream(file, false); // Open for writing, truncate
        } else if ((flags & O_WRONLY) != 0) {
            fos = new FileOutputStream(file, true); // Open for appending
        } else {
            throw new IOException("Invalid flags combination.");
        }

        return fos;
    }
}