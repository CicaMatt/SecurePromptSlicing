import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {

    public static void main(String[] args) {
        String fileName = "important_config";
        createAndOpenFile(fileName);
        writeFile(fileName, "This is an important configuration file.");
    }

    private static void createAndOpenFile(String fileName) {
        File file = new File(fileName);

        // Check if the file exists; if not, create it
        if (!file.exists()) {
            try {
                boolean created = file.createNewFile();
                if (created) {
                    System.out.println("File created: " + file.getName());
                } else {
                    System.err.println("Failed to create the file.");
                }
            } catch (IOException e) {
                e.printStackTrace();
            }
        }

        // Open for reading and writing
        try (FileInputStream fis = new FileInputStream(file);
             FileOutputStream fos = new FileOutputStream(file)) {

            System.out.println("File opened successfully.");

            // Demonstration of read/write operations can be done here

        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    private static void writeFile(String fileName, String content) {
        File file = new File(fileName);

        try (FileOutputStream fos = new FileOutputStream(file)) {
            byte[] bytes = content.getBytes();

            fos.write(bytes);
            System.out.println("Content written to the file.");

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}