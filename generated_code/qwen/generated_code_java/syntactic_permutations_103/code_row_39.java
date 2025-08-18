import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFileExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        File file = new File(filePath);

        try {
            // O_CREAT: Create the file if it doesn't exist
            // O_TRUNC: Truncate the file to 0 bytes if it already exists
            // O_WRONLY: Open the file for writing only
            // O_EXCL: Throw an exception if the file already exists when creating

            boolean fileCreated = file.createNewFile();
            if (!fileCreated) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }

            FileOutputStream fos = new FileOutputStream(file, false); // false for O_TRUNC
            fos.write("Hello, world!".getBytes());
            fos.close();

        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }
}