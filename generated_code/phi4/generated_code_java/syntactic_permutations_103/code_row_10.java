import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String filePath = "example.txt"; // specify your file path here

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            fos.write(0); // Write a single null byte to create the file
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }
    }
}