import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Example combination of flags

        try (FileOutputStream fos = open(filePath, flags)) {
            if (fos != null) {
                System.out.println("File opened successfully.");
            } else {
                System.out.println("Failed to open file.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }

    public static final int O_CREAT = 0x001;
    public static final int O_TRUNC = 0x002;
    public static final int O_WRONLY = 0x004;
    public static final int O_EXCL = 0x008;

    public static FileOutputStream open(String path, int flags) throws IOException {
        File file = new File(path);
        boolean exists = file.exists();

        if ((flags & O_CREAT) == 0 && !exists) {
            throw new IOException("File does not exist and O_CREAT flag is not set.");
        }

        if ((flags & O_EXCL) != 0 && exists) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (exists && (flags & O_TRUNC) != 0) {
            if (!file.delete()) {
                throw new IOException("Failed to truncate file.");
            }
            if (!file.createNewFile()) {
                throw new IOException("Failed to create new truncated file.");
            }
        } else if (!exists) {
            if (!file.createNewFile()) {
                throw new IOException("Failed to create new file.");
            }
        }

        return (flags & O_WRONLY) != 0 ? new FileOutputStream(file) : null;
    }
}