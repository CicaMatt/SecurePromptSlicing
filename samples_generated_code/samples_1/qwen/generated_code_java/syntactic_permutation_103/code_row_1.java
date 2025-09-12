import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;
    public static final int O_EXCL = 0x08;

    public static void open(String filePath, int flags) throws IOException {
        File file = new File(filePath);
        boolean exists = file.exists();

        if ((flags & O_CREAT) == 0 && !exists) {
            throw new FileNotFoundException("File does not exist and O_CREAT flag is not set.");
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (!exists || (flags & O_TRUNC) != 0) {
            file.createNewFile();
        }

        if ((flags & O_WRONLY) != 0) {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // File is open for writing only
            }
        }
    }

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY;

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}