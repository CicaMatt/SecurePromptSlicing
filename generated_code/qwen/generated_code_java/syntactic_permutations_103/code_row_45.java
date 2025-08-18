import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
            open(filePath, flags);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_RDONLY = 0x0000;
    private static final int O_WRONLY = 0x0001;
    private static final int O_RDWR = 0x0002;
    private static final int O_CREAT = 0x0200;
    private static final int O_EXCL = 0x0800;
    private static final int O_TRUNC = 0x0400;

    public static FileDescriptor open(String path, int flags) throws IOException {
        if ((flags & O_WRONLY) != O_WRONLY && (flags & O_RDWR) != O_RDWR) {
            throw new IllegalArgumentException("Unsupported mode");
        }

        boolean create = (flags & O_CREAT) == O_CREAT;
        boolean exclusive = (flags & O_EXCL) == O_EXCL;
        boolean truncate = (flags & O_TRUNC) == O_TRUNC;

        FileDescriptor fd = null;
        FileOutputStream fos = null;

        try {
            java.io.File file = new java.io.File(path);
            if (!file.exists()) {
                if (!create) {
                    throw new IOException("File does not exist and O_CREAT flag is not set");
                }
                if (exclusive && file.createNewFile()) {
                    fd = new FileDescriptor();
                    fos = new FileOutputStream(file, false);
                } else if (exclusive) {
                    throw new IOException("File already exists and O_EXCL flag is set");
                } else {
                    fd = new FileDescriptor();
                    fos = new FileOutputStream(file, false);
                }
            } else {
                if (exclusive) {
                    throw new IOException("File already exists and O_EXCL flag is set");
                }
                fd = new FileDescriptor();
                fos = new FileOutputStream(file, !truncate);
            }

        } catch (IOException e) {
            if (fos != null) {
                fos.close();
            }
            throw e;
        }

        return fd;
    }
}