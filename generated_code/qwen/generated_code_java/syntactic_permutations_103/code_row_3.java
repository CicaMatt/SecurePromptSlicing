import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            open(filePath, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    private static final int O_RDONLY = 0x000;
    private static final int O_WRONLY = 0x001;
    private static final int O_RDWR = 0x002;
    private static final int O_CREAT = 0x100;
    private static final int O_EXCL = 0x200;
    private static final int O_TRUNC = 0x400;

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);
        boolean fileExists = file.exists();

        if ((flags & O_CREAT) != 0 && !fileExists) {
            file.createNewFile();
        }

        if ((flags & O_EXCL) != 0 && fileExists) {
            throw new IOException("File already exists");
        }

        if ((flags & O_TRUNC) != 0 && fileExists) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close();
        }
    }
}