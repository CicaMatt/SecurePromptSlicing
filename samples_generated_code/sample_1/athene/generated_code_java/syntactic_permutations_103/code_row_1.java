import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        try {
            String filename = "example.txt";
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean writeOnly = true;
            boolean failIfExists = false;

            int flags = 0;
            if (createIfNotExists) flags |= O_CREAT;
            if (truncateIfExists) flags |= O_TRUNC;
            if (writeOnly) flags |= O_WRONLY;
            if (failIfExists) flags |= O_EXCL;

            open(filename, flags);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 0x01;
    private static final int O_TRUNC = 0x02;
    private static final int O_WRONLY = 0x04;
    private static final int O_EXCL = 0x08;

    public static void open(String filename, int flags) throws Exception {
        File file = new File(filename);
        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new Exception("File already exists");
        }
        if (!file.exists() && (flags & O_CREAT) != 0) {
            if (!file.createNewFile()) {
                throw new Exception("Failed to create file");
            }
        } else if (file.exists() && (flags & O_TRUNC) != 0) {
            if (!file.setLength(0)) {
                throw new Exception("Failed to truncate file");
            }
        }

        RandomAccessFile raf = new RandomAccessFile(file, ((flags & O_WRONLY) != 0) ? "rw" : "r");
        // File is now open for writing or reading based on flags
        raf.close();
    }
}