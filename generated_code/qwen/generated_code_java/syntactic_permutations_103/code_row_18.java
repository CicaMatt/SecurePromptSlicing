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

    public static final int O_CREAT = 0x001;
    public static final int O_TRUNC = 0x002;
    public static final int O_WRONLY = 0x004;
    public static final int O_EXCL = 0x008;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists.");
        }

        if (file.exists() && (flags & O_TRUNC) != 0) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close();
        }
    }
}