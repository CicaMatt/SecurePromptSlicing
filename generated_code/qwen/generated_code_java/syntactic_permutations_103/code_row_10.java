import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // | O_EXCL if you want to fail if the file exists

        try {
            FileOutputStream fos = createFile(filePath, flags);
            fos.write("Hello, world!".getBytes());
            fos.close();
        } catch (IOException e) {
            System.err.println("Error creating or writing to file: " + e.getMessage());
        }
    }

    private static final int O_CREAT = 0x001;
    private static final int O_TRUNC = 0x002;
    private static final int O_WRONLY = 0x004;
    private static final int O_EXCL = 0x008;

    public static FileOutputStream createFile(String path, int flags) throws IOException {
        boolean createNewFile = (flags & O_CREAT) != 0;
        boolean truncateExisting = (flags & O_TRUNC) != 0;
        boolean writeOnly = (flags & O_WRONLY) != 0;
        boolean failIfExists = (flags & O_EXCL) != 0;

        if (writeOnly && createNewFile) {
            java.io.File file = new java.io.File(path);
            if (failIfExists && file.exists()) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }
            boolean createdOrTruncated = false;
            if (!file.exists() || truncateExisting) {
                createdOrTruncated = file.createNewFile();
                if (truncateExisting && file.exists()) {
                    try (FileOutputStream fos = new FileOutputStream(file, false)) {
                        // Truncate the file by opening it in write mode without appending
                    }
                }
            }
            if (createdOrTruncated || !failIfExists) {
                return new FileOutputStream(file, false);
            } else {
                throw new IOException("Failed to create or truncate the file.");
            }
        } else {
            throw new IllegalArgumentException("Unsupported flag combination.");
        }
    }
}