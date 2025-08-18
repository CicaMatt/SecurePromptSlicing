import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            open(filePath, true, true, false);
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }

    public static void open(String path, boolean create, boolean truncate, boolean exclusive) throws IOException {
        File file = new File(path);

        if (!create && !file.exists()) {
            throw new IOException("File does not exist and creation is disabled.");
        }

        if (exclusive && file.exists()) {
            throw new IOException("File already exists and exclusive creation is requested.");
        }

        FileOutputStream fos;
        if (truncate || !file.exists()) {
            fos = new FileOutputStream(file);
        } else {
            fos = new FileOutputStream(file, true);
        }

        fos.close();
    }
}