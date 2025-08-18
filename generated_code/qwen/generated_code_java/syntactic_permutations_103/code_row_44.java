import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example usage of flags

        try {
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;
    public static final int O_EXCL = 0x08;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File exists and O_EXCL flag is set.");
        }

        if (file.exists() && (flags & O_TRUNC) != 0) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close(); // Open for writing
        }
    }
}