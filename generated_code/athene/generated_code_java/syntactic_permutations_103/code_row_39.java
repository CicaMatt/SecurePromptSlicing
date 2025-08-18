import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean writeOnly = true;
            boolean exclusiveCreation = false; // O_EXCL is not used in this example

            int flags = 0;
            if (createIfNotExists) {
                flags |= RandomAccessFile.CREATE;
            }
            if (truncateIfExists) {
                flags |= RandomAccessFile.TRUNCATE;
            }
            if (writeOnly) {
                flags |= RandomAccessFile.WRITE_ONLY;
            }

            RandomAccessFile raf = open(filePath, flags);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static RandomAccessFile open(String filePath, int flags) throws Exception {
        File file = new File(filePath);
        String mode = "rw"; // Default mode

        if ((flags & RandomAccessFile.WRITE_ONLY) != 0) {
            mode = "rws";
        }

        if (file.exists()) {
            if ((flags & RandomAccessFile.TRUNCATE) != 0) {
                file.delete();
                file.createNewFile();
            }
        } else {
            if ((flags & RandomAccessFile.CREATE) != 0) {
                if ((flags & RandomAccessFile.EXCLUSIVE_CREATE) != 0 && file.exists()) {
                    throw new Exception("File already exists and O_EXCL flag is set.");
                }
                file.createNewFile();
            }
        }

        return new RandomAccessFile(file, mode);
    }
}

class RandomAccessFile {
    static final int CREATE = 1;
    static final int TRUNCATE = 2;
    static final int WRITE_ONLY = 4;
    static final int EXCLUSIVE_CREATE = 8;

    private java.io.RandomAccessFile raf;

    public RandomAccessFile(File file, String mode) throws Exception {
        this.raf = new java.io.RandomAccessFile(file, mode);
    }

    public void close() throws Exception {
        raf.close();
    }
}