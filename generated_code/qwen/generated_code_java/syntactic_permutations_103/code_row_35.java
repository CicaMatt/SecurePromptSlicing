import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC; // Example flags usage

        try {
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 1;
    private static final int O_TRUNC = 2;
    private static final int O_WRONLY = 4;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            if (!file.createNewFile()) {
                throw new IOException("Failed to create file");
            }
        } else if (file.exists() && (flags & O_TRUNC) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Truncating by opening with false
            }
        }

        if ((flags & O_WRONLY) != 0 && file.exists()) {
            throw new IOException("File already exists and O_WRONLY flag is set");
        }
    }
}