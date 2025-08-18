import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createNewFile = true; // O_CREAT
        boolean truncateExistingFile = true; // O_TRUNC
        boolean openForWritingOnly = true; // O_WRONLY
        boolean failIfFileExists = false; // O_EXCL

        try (FileOutputStream fos = getFileOutputStream(filePath, createNewFile, truncateExistingFile, failIfFileExists)) {
            if (openForWritingOnly) {
                String message = "Hello, world!";
                fos.write(message.getBytes());
            }
        } catch (IOException e) {
            System.err.println("Error opening or writing to file: " + e.getMessage());
        }
    }

    private static FileOutputStream getFileOutputStream(String filePath, boolean createNewFile, boolean truncateExistingFile, boolean failIfFileExists) throws IOException {
        int flags = 0;
        if (createNewFile) {
            flags |= 1; // O_CREAT
        }
        if (truncateExistingFile) {
            flags |= 2; // O_TRUNC
        }
        if (failIfFileExists && createNewFile) {
            flags |= 4; // O_EXCL
        }

        boolean fileExists = java.nio.file.Files.exists(java.nio.file.Paths.get(filePath));
        if (fileExists) {
            if (failIfFileExists) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }
            if (truncateExistingFile) {
                new java.io.File(filePath).delete();
                return new FileOutputStream(filePath);
            }
        } else if (!fileExists && createNewFile) {
            return new FileOutputStream(filePath, false); // Open for writing, do not append
        }

        throw new IOException("Failed to open file with specified flags.");
    }
}