import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;

        try {
            open(filePath, flags);
            System.out.println("File operation successful.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static final int O_RDONLY = 0x000;
    public static final int O_WRONLY = 0x001;
    public static final int O_RDWR = 0x002;
    public static final int O_CREAT = 0x040;
    public static final int O_EXCL = 0x080;
    public static final int O_TRUNC = 0x200;

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);

        if ((flags & O_CREAT) != 0) {
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if ((flags & O_EXCL) != 0) {
                    throw new IOException("File already exists and O_EXCL flag is set.");
                }
            }
        }

        if ((flags & O_TRUNC) != 0 && file.exists()) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Truncating the file by opening it in write mode without appending
            }
        }

        if ((flags & O_WRONLY) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Opening the file for writing only
            }
        } else {
            throw new UnsupportedOperationException("Only O_WRONLY flag is supported in this implementation.");
        }
    }
}