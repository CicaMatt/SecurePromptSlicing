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
            if (createIfNotExists) flags |= 1; // O_CREAT
            if (truncateIfExists) flags |= 2; // O_TRUNC
            if (failIfExists) flags |= 4; // O_EXCL

            open(filename, flags);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void open(String filename, int flags) throws Exception {
        File file = new File(filename);
        boolean createNewFile = (flags & 1) != 0;
        boolean truncateFile = (flags & 2) != 0;
        boolean exclusive = (flags & 4) != 0;

        if (exclusive && file.exists()) {
            throw new Exception("File already exists and O_EXCL flag is set.");
        }

        RandomAccessFile raf;
        if (!file.exists() && createNewFile) {
            file.createNewFile();
        }

        if (truncateFile && file.exists()) {
            file.delete();
            file.createNewFile();
        }

        raf = new RandomAccessFile(file, "rw");
        raf.close();
    }
}