import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_EXCL;

        try {
            open(fileName, flags);
            System.out.println("File operation successful.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_EXCL = 0x04;

    public static void open(String fileName, int flags) throws IOException {
        File file = new File(fileName);
        
        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists.");
        }

        if ((flags & O_TRUNC) != 0 && file.exists()) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Truncates the file to zero length
            }
        }

        if (!file.canWrite()) {
            throw new IOException("Cannot open file for writing.");
        }
    }
}