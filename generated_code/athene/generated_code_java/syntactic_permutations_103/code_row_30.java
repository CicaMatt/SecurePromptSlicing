import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void open(String filePath, int flags) throws IOException {
        boolean create = (flags & 0x01) != 0; // O_CREAT
        boolean truncate = (flags & 0x02) != 0; // O_TRUNC
        boolean writeOnly = (flags & 0x04) != 0; // O_WRONLY
        boolean exclusive = (flags & 0x08) != 0; // O_EXCL

        File file = new File(filePath);
        if (exclusive && file.exists()) {
            throw new IOException("File already exists");
        }

        FileOutputStream fos;
        if (create || truncate) {
            if (!file.exists() && create) {
                file.createNewFile();
            }
            fos = new FileOutputStream(file, false); // Always truncate when opening
        } else {
            fos = new FileOutputStream(file);
        }

        // Use the stream for writing
        fos.close(); // Close the stream after use
    }

    public static void main(String[] args) {
        try {
            open("test.txt", 0x01 | 0x02 | 0x04); // O_CREAT | O_TRUNC | O_WRONLY
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}