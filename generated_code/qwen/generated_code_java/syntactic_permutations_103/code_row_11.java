import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_WRONLY | O_EXCL;

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 0x020;
    private static final int O_WRONLY = 0x001;
    private static final int O_EXCL = 0x200;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists.");
        }

        if ((flags & O_WRONLY) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file)) {
                // File is open for writing
            }
        } else {
            throw new IllegalArgumentException("Unsupported flags combination.");
        }
    }
}