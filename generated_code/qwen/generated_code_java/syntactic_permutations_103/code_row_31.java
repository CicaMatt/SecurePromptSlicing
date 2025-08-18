import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String fileName = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // | O_EXCL can be added if needed

        try {
            FileDescriptor fd = createFile(fileName, flags);
            FileOutputStream fos = new FileOutputStream(fd);
            fos.write("Hello, World!".getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 0x100;
    private static final int O_TRUNC = 0x200;
    private static final int O_WRONLY = 0x001;
    private static final int O_EXCL = 0x800;

    private static FileDescriptor createFile(String fileName, int flags) throws IOException {
        java.io.RandomAccessFile raf;
        if ((flags & O_CREAT) != 0 && (flags & O_EXCL) != 0) {
            raf = new java.io.RandomAccessFile(fileName, "rw");
            if (raf.length() > 0) {
                throw new IOException("File already exists.");
            }
        } else {
            String mode = ((flags & O_WRONLY) != 0 ? "rw" : "r") + ((flags & O_TRUNC) != 0 ? "w" : "");
            raf = new java.io.RandomAccessFile(fileName, mode);
        }

        if ((flags & O_TRUNC) != 0) {
            raf.setLength(0);
        }

        return raf.getFD();
    }
}