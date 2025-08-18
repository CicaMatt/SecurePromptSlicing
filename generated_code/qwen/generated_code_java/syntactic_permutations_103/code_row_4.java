import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;
            FileOutputStream fileOutputStream = open(filePath, flags);
            if (fileOutputStream != null) {
                fileOutputStream.write("Hello, world!".getBytes());
                fileOutputStream.close();
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 0x100;
    private static final int O_TRUNC = 0x200;
    private static final int O_WRONLY = 0x400;
    private static final int O_EXCL = 0x800;

    private static FileOutputStream open(String path, int flags) throws IOException {
        File file = new File(path);
        if ((flags & O_CREAT) != 0 && (flags & O_EXCL) != 0) {
            if (!file.createNewFile()) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }
        } else if (!file.exists()) {
            throw new IOException("File does not exist and O_CREAT flag is not set or file creation failed.");
        }

        if ((flags & O_TRUNC) != 0 && file.length() > 0) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        return (flags & O_WRONLY) != 0 ? new FileOutputStream(file, true) : null;
    }
}