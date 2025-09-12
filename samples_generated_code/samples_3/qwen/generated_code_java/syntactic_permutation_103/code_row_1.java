import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static final int O_CREAT = 0x100;
    public static final int O_TRUNC = 0x200;
    public static final int O_WRONLY = 0x400;
    public static final int O_EXCL = 0x800;

    public static FileOutputStream open(String path, int flags) throws IOException {
        File file = new File(path);
        boolean exists = file.exists();

        if ((flags & O_CREAT) == 0 && !exists) {
            throw new FileNotFoundException("File does not exist and O_CREAT flag is not set.");
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (!file.exists() || (flags & O_CREAT) != 0) {
            file.createNewFile();
        }

        boolean truncate = (flags & O_TRUNC) != 0;
        FileOutputStream fos = new FileOutputStream(file, (flags & O_WRONLY) != 0 && !truncate);

        if (truncate) {
            fos.getChannel().truncate(0);
        }

        return fos;
    }

    public static void main(String[] args) {
        try {
            FileOutputStream fos = open("example.txt", O_CREAT | O_TRUNC | O_WRONLY);
            fos.write("Hello, World!".getBytes());
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}