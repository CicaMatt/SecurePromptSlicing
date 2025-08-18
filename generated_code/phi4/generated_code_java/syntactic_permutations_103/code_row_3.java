import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {

    public static void main(String[] args) {
        String fileName = "example.txt";

        try (FileOutputStream fos = new FileOutputStream(fileName, false)) {
            System.out.println("File opened for writing.");
        } catch (IOException e) {
            if (!new File(fileName).exists()) {
                try {
                    // Create a new file and open it for writing
                    File file = new File(fileName);
                    if (file.createNewFile()) {
                        try (FileOutputStream fos = new FileOutputStream(file)) {
                            System.out.println("New file created and opened for writing.");
                        }
                    } else {
                        System.out.println("Failed to create the file: " + fileName);
                    }
                } catch (IOException ex) {
                    System.err.println("An error occurred while creating the file: " + ex.getMessage());
                }
            } else {
                System.err.println("The file already exists and cannot be opened with O_EXCL.");
            }
        }

    }

}