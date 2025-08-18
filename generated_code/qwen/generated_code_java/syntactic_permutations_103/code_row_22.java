import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createIfNotExists = true; // O_CREAT
        boolean truncateIfExists = true; // O_TRUNC
        boolean writeOnly = true; // O_WRONLY
        boolean failIfExists = false; // O_EXCL

        try {
            File file = new File(filePath);
            if (file.exists()) {
                if (failIfExists) {
                    throw new IOException("File already exists and O_EXCL is set.");
                }
                if (truncateIfExists) {
                    FileOutputStream fos = new FileOutputStream(file, false); // Open in write mode without append
                    fos.close();
                }
            } else {
                if (createIfNotExists) {
                    file.createNewFile();
                } else {
                    throw new IOException("File does not exist and O_CREAT is not set.");
                }
            }

            if (writeOnly) {
                FileOutputStream fos = new FileOutputStream(file, true); // Open in write mode
                fos.write("Hello, world!".getBytes());
                fos.close();
            }

        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}