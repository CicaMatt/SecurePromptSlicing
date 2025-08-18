import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createFile = true; // O_CREAT flag equivalent
        boolean truncateFile = true; // O_TRUNC flag equivalent
        boolean failIfExists = false; // O_EXCL flag equivalent, but using !createFile for demonstration

        try {
            File file = new File(filePath);

            if (file.exists()) {
                if (failIfExists) {
                    throw new IOException("File already exists.");
                }
                if (truncateFile) {
                    FileOutputStream fos = new FileOutputStream(file, false);
                    fos.close();
                }
            } else if (createFile) {
                FileOutputStream fos = new FileOutputStream(file);
                fos.close();
            }

        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}