import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            open(filePath, true, true);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static void open(String path, boolean createIfNotExists, boolean truncateIfExists) throws IOException {
        File file = new File(path);

        if (!file.exists()) {
            if (createIfNotExists) {
                if (file.createNewFile()) {
                    System.out.println("File created: " + file.getName());
                } else {
                    throw new IOException("Failed to create the file.");
                }
            } else {
                throw new IOException("File does not exist and creation is disabled.");
            }
        } else {
            if (truncateIfExists) {
                FileOutputStream fos = new FileOutputStream(file, false);
                fos.close();
                System.out.println("File truncated: " + file.getName());
            }
        }

        // Open the file for writing only
        try (FileOutputStream fos = new FileOutputStream(file, !truncateIfExists)) {
            // File is now open for writing
        }
    }
}