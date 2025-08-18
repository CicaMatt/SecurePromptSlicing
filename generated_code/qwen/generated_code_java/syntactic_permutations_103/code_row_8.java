import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            // O_WRONLY: Open for writing only.
            // O_CREAT: Create file if it does not exist (handled by FileOutputStream).
            // O_TRUNC: Truncate the file to 0 bytes if it already exists.
            // O_EXCL: Fail if the file already exists (not directly supported, handled manually).

            File file = new File(fileName);
            boolean fileExists = file.exists();

            if (fileExists) {
                throw new IOException("File already exists. (O_EXCL)");
            }

            FileOutputStream fos = new FileOutputStream(file, false); // 'false' for O_TRUNC
            fos.close();
            System.out.println("File opened/created successfully with O_WRONLY, O_CREAT, O_TRUNC, and O_EXCL flags.");
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}