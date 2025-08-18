import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // | O_EXCL to fail if file exists

        try {
            FileDescriptor fd = createFile(filePath, flags);
            FileOutputStream fos = new FileOutputStream(fd);
            fos.write("Hello, World!".getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 0x40;
    private static final int O_TRUNC = 0x200;
    private static final int O_WRONLY = 0x1;
    private static final int O_EXCL = 0x80;

    private static FileDescriptor createFile(String filePath, int flags) throws IOException {
        if ((flags & O_CREAT) == 0) {
            throw new IllegalArgumentException("O_CREAT flag must be set");
        }

        FileDescriptor fd = new FileDescriptor();
        java.io.File file = new java.io.File(filePath);

        if ((flags & O_EXCL) != 0 && file.exists()) {
            throw new IOException("File already exists and O_EXCL is set");
        }

        if (!file.exists() || (flags & O_TRUNC) != 0) {
            java.nio.file.Files.write(file.toPath(), new byte[0]);
        }

        fd = new FileOutputStream(file, (flags & O_WRONLY) != 0).getFD();

        return fd;
    }
}