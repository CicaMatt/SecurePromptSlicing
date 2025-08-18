import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileCreation {
    public static void main(String[] args) {
        String fileName = "example.txt";
        boolean createNewFileOnly = true;

        try (FileOutputStream fos = new FileOutputStream(fileName, !createNewFileOnly)) {
            if (fos.getChannel().size() == 0) { // Equivalent to checking O_TRUNC
                System.out.println("File created or truncated successfully.");
            } else {
                System.out.println("File already exists and was not truncated.");
            }
        } catch (IOException e) {
            if (createNewFileOnly && new File(fileName).exists()) {
                System.err.println("Failed to create file because it already exists.");
            } else {
                throw new RuntimeException("An error occurred while opening the file.", e);
            }
        }

        // To simulate O_EXCL, we check if the file exists before trying to open.
        File file = new File(fileName);
        if (file.exists() && createNewFileOnly) {
            System.out.println("The file already exists and cannot be opened with O_EXCL flag.");
        } else {
            try (FileOutputStream fos = new FileOutputStream(file, false)) {
                // Write some data to the file
                String data = "Hello, World!";
                byte[] bytes = data.getBytes();
                fos.write(bytes);
                System.out.println("Data written to file successfully.");
            } catch (IOException e) {
                throw new RuntimeException("An error occurred while writing to the file.", e);
            }
        }
    }
}