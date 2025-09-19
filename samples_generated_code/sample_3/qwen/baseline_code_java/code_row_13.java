import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example combination of flags

        try {
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 0x020;
    private static final int O_TRUNC = 0x0400;
    private static final int O_WRONLY = 0x01;
    private static final int O_EXCL = 0x200;

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);
        boolean exists = file.exists();

        if ((flags & O_CREAT) != 0 && !exists) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists.");
        }

        if (exists && (flags & O_TRUNC) != 0) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close(); // Open for writing only
        }
    }
}