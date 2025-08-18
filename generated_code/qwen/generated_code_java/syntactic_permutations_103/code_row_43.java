import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class OpenFileExample {

    private static final int O_CREAT = 1;
    private static final int O_TRUNC = 2;
    private static final int O_WRONLY = 4;
    private static final int O_EXCL = 8;

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example usage of flags

        try {
            FileOutputStream fos = open(filePath, flags);
            if (fos != null) {
                System.out.println("File opened successfully.");
                fos.close();
            }
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static FileOutputStream open(String path, int flags) throws IOException {
        Path filePath = Paths.get(path);
        boolean exists = Files.exists(filePath);

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if ((flags & O_CREAT) != 0 && !exists) {
            Files.createFile(filePath);
        }

        FileOutputStream fos;
        if ((flags & O_WRONLY) != 0) {
            fos = new FileOutputStream(filePath.toString(), (flags & O_TRUNC) != 0);
        } else {
            throw new UnsupportedOperationException("Only O_WRONLY flag is supported in this implementation.");
        }

        return fos;
    }
}