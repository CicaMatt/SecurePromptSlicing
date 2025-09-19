import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpenExample {

    public static void main(String[] args) {
        String fileName = "example.txt";

        try {
            // Flags equivalent: O_CREAT | O_TRUNC | O_WRONLY | O_EXCL
            boolean createdNew = new FileOutputStream(fileName, false).close();
            if (!createdNew) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }

            // File was created successfully as it did not exist before.
            System.out.println("File created: " + fileName);

        } catch (IOException e) {
            System.err.println(e.getMessage());
        }
    }
}