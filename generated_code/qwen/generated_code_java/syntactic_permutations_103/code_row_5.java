import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;

        try {
            FileDescriptor fd = open(filePath, flags);
            FileOutputStream fos = new FileOutputStream(fd);
            fos.write("Hello, World!".getBytes());
            fos.close();
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 0x40;
    private static final int O_TRUNC = 0x200;
    private static final int O_WRONLY = 0x1;
    private static final int O_EXCL = 0x80;

    private static FileDescriptor open(String path, int flags) throws IOException {
        if ((flags & O_CREAT) != 0 && (flags & O_EXCL) != 0) {
            File f = new File(path);
            if (f.exists()) {
                throw new IOException("File already exists");
            }
        }

        FileOutputStream fos;
        try {
            fos = new FileOutputStream(new File(path), (flags & (O_WRONLY | O_TRUNC)) == O_WRONLY && (flags & O_TRUNC) != 0);
        } catch (IOException e) {
            if ((flags & O_CREAT) != 0) {
                fos = new FileOutputStream(new File(path));
            } else {
                throw e;
            }
        }

        return fos.getFD();
    }
}