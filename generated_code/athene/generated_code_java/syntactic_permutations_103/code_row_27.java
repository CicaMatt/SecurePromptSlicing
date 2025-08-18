import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileHandler {
    public static void main(String[] args) {
        String fileName = "example.txt";
        boolean createIfNotExists = true;
        boolean truncateIfExists = true;
        boolean writeOnly = true;
        boolean failIfExists = false;

        try (FileOutputStream fos = open(fileName, createIfNotExists, truncateIfExists, writeOnly, failIfExists)) {
            // File is now opened according to the specified flags
        } catch (IOException e) {
            System.out.println("Error opening file: " + e.getMessage());
        }
    }

    public static FileOutputStream open(String fileName, boolean createIfNotExists, boolean truncateIfExists, boolean writeOnly, boolean failIfExists) throws IOException {
        File file = new File(fileName);
        if (file.exists()) {
            if (failIfExists) {
                throw new IOException("File already exists and O_EXCL flag is set.");
            }
            if (truncateIfExists) {
                file.delete();
                file.createNewFile();
            }
        } else {
            if (createIfNotExists) {
                file.createNewFile();
            } else {
                throw new IOException("File does not exist and O_CREAT flag is not set.");
            }
        }

        return new FileOutputStream(file, false); // Always truncate when opening for writing
    }
}