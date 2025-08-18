import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = 0x241; // O_CREAT | O_TRUNC | O_WRONLY | O_EXCL in octal

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);
        boolean createNewFile = false;

        if ((flags & 0x40) != 0) { // O_CREAT
            createNewFile = true;
        }

        if ((flags & 0x200) != 0 && file.exists()) { // O_TRUNC
            file.delete();
            createNewFile = true;
        }

        if ((flags & 0x100) != 0 && !file.canWrite()) { // O_WRONLY
            throw new IOException("File cannot be opened for writing only.");
        }

        if ((flags & 0x800) != 0 && file.exists()) { // O_EXCL
            throw new IOException("File already exists.");
        }

        if (createNewFile) {
            if (!file.createNewFile()) {
                throw new IOException("Failed to create new file.");
            }
        }

        FileOutputStream fos = new FileOutputStream(file, false);
    }
}