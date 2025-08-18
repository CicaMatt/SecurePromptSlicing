import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String filePath = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            // The file is created and opened for writing only.
            System.out.println("File created or truncated successfully.");
        } catch (IOException e) {
            if (e.getMessage().contains("exists")) {
                System.out.println("The file already exists.");
            } else {
                e.printStackTrace();
            }
        }
    }

}