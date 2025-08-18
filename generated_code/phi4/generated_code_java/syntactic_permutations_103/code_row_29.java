import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperation {

    public static void main(String[] args) {
        String filePath = "example.txt";

        // Create a new file or open an existing one, truncate it to 0 bytes if it exists
        try (FileOutputStream fos = new FileOutputStream(filePath, false)) {
            System.out.println("File created or truncated successfully.");
        } catch (IOException e) {
            System.err.println("An error occurred: " + e.getMessage());
        }

        // Attempt to create a file with O_EXCL flag behavior manually
        File file = new File(filePath);
        if (!file.exists()) {
            try {
                boolean createdNew = file.createNewFile();
                if (createdNew) {
                    System.out.println("Exclusive creation of the file succeeded.");
                } else {
                    System.err.println("The file already exists.");
                }
            } catch (IOException e) {
                System.err.println("An error occurred: " + e.getMessage());
            }
        } else {
            System.err.println("File with O_EXCL flag behavior failed: File already exists.");
        }
    }
}