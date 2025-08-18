import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_RDONLY = 0x0000; // Open for reading only.
    private static final int O_WRONLY = 0x0001; // Open for writing only.
    private static final int O_RDWR = 0x0002;   // Open for reading and writing.
    private static final int O_CREAT = 0x0100;  // Create file if it does not exist.
    private static final int O_EXCL = 0x0800;  // Exclusive use flag.
    private static final int O_TRUNC = 0x0200;  // Truncate file to zero length or create a new, empty file.

    public static FileOutputStream open(String path, int flags) throws IOException {
        FileDescriptor fd = new FileDescriptor();
        boolean append = false;
        boolean createNew = (flags & O_CREAT) != 0;
        boolean truncateExisting = (flags & O_TRUNC) != 0;
        boolean exclusiveCreate = (flags & O_EXCL) != 0;

        if ((flags & O_WRONLY) != 0 || (flags & O_RDWR) != 0) {
            FileOutputStream fos = new FileOutputStream(path, append);
            if (createNew && exclusiveCreate) {
                try {
                    if (!new File(path).createNewFile()) {
                        throw new IOException("File already exists");
                    }
                } catch (IOException e) {
                    fos.close();
                    throw e;
                }
            }

            if (truncateExisting) {
                fos.getChannel().truncate(0);
            }

            return fos;
        } else {
            throw new IllegalArgumentException("Unsupported flags combination");
        }
    }
}