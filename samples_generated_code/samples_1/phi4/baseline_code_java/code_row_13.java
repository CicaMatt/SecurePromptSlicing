import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // If the file exists and O_EXCL flag is considered,
            // FileOutputStream will throw an exception if file exists.
            if (!new File(filePath).exists()) {
                System.out.println("File created: " + filePath);
            } else {
                System.out.println("File already exists. Truncating.");
            }

            fos.write(0); // Write a single byte to ensure the file is not empty
        } catch (IOException e) {
            System.err.println("Could not create or open the file: " + e.getMessage());
        }
    }
}