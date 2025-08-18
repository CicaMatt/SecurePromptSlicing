import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean openForWritingOnly = true;
            boolean failIfExists = false;

            int flags = 0;
            if (createIfNotExists) flags |= 1; // O_CREAT
            if (truncateIfExists) flags |= 2; // O_TRUNC
            if (openForWritingOnly) flags |= 4; // O_WRONLY
            if (failIfExists) flags |= 8; // O_EXCL

            open(filePath, flags);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static void open(String filePath, int flags) throws Exception {
        File file = new File(filePath);

        if ((flags & 8) != 0 && file.exists()) { // O_EXCL
            throw new Exception("File already exists and O_EXCL flag is set.");
        }

        RandomAccessFile raf;
        if ((flags & 4) != 0) { // O_WRONLY
            if ((flags & 1) != 0) { // O_CREAT
                if (!file.exists()) {
                    file.createNewFile();
                }
            }
            if ((flags & 2) != 0 && file.exists()) { // O_TRUNC
                file.delete();
                file.createNewFile();
            }
            raf = new RandomAccessFile(file, "rw");
            raf.setLength(0); // Truncate to 0 bytes after opening for consistency
        } else {
            throw new Exception("Unsupported flags combination.");
        }

        raf.close();
    }
}