import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_WRONLY | O_EXCL; // Flags for creating or opening the file

        try {
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x001;
    public static final int O_WRONLY = 0x002;
    public static final int O_EXCL = 0x004;

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);
        
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            // Create a new file
            boolean created = file.createNewFile();
            if (!created) {
                throw new IOException("Failed to create the file.");
            }
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if ((flags & O_WRONLY) != 0) {
            // Open file for writing
            try (FileOutputStream fos = new FileOutputStream(file)) {
                System.out.println("File opened in write-only mode.");
            }
        } else {
            throw new IOException("Unsupported flags combination.");
        }
    }
}