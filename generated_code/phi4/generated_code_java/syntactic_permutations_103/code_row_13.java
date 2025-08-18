import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String fileName = "example.txt";

        // Equivalent behavior of the described flags using Java's File and FileOutputStream
        try (FileOutputStream fos = new FileOutputStream(new File(fileName), false)) {
            if (!new File(fileName).exists()) {
                // Equivalent to O_CREAT, O_EXCL: create file only if it does not exist
                System.out.println("File created successfully.");
            } else {
                // Equivalent to O_TRUNC: truncate the file if it already exists
                System.out.println("Existing file truncated and opened for writing.");
            }
        } catch (IOException e) {
            System.err.println("Failed to create or open file. It might already exist.");
        }
    }
}