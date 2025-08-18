import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Failed to open file: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;
    public static final int O_EXCL = 0x08;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            if (!file.createNewFile()) {
                throw new IOException("Failed to create file.");
            }
        } else if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists.");
        }

        if (file.exists() && (flags & O_TRUNC) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Truncating the file by opening it in write mode with false append flag
            }
        }

        if ((flags & O_WRONLY) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // File opened for writing only
            }
        }
    }
}