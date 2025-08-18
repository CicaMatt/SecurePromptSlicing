import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreator {

    public static void main(String[] args) {
        String fileName = "example.txt";
        
        try (FileOutputStream fos = new FileOutputStream(fileName, false)) {
            // The file is created and truncated to 0 bytes if it already exists
            System.out.println("File created or opened successfully.");
        } catch (IOException e) {
            if (e.getMessage().contains("exists")) {
                System.err.println("The file already exists. Aborting creation due to O_EXCL flag.");
            } else {
                e.printStackTrace();
            }
        }
    }
}