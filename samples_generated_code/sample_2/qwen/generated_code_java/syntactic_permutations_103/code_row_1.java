import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;
    public static final int O_EXCL = 0x08;

    public static void open(String path, int flags) throws IOException {
        File file = new File(path);

        if ((flags & O_CREAT) != 0) {
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if ((flags & O_EXCL) != 0) {
                    throw new IOException("File already exists and O_EXCL flag is set.");
                }
            }
        }

        if ((flags & O_TRUNC) != 0 && file.exists()) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if ((flags & O_WRONLY) != 0) {
            new FileOutputStream(file, true).close(); // Open for writing
        }
    }
}