import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createFile = true; // Equivalent of O_CREAT
        boolean truncateFile = true; // Equivalent of O_TRUNC
        boolean writeOnly = true; // Equivalent of O_WRONLY
        boolean failIfExists = true; // Equivalent of O_EXCL

        try {
            if (createFile) {
                if (failIfExists && new java.io.File(filePath).exists()) {
                    throw new IOException("File already exists and O_EXCL flag is set.");
                }
                FileOutputStream fileOutputStream = new FileOutputStream(filePath, !truncateFile);
                if (writeOnly) {
                    // Writing to the file can be done here
                    fileOutputStream.write("Hello, world!".getBytes());
                }
                fileOutputStream.close();
            } else {
                throw new IOException("O_CREAT flag is not set, cannot create or open the file.");
            }
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}