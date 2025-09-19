import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createIfNotExists = true;
        boolean truncateIfExists = true;
        boolean writeOnly = true;
        boolean failIfAlreadyExists = false;

        try {
            open(filePath, createIfNotExists, truncateIfExists, writeOnly, failIfAlreadyExists);
        } catch (IOException e) {
            System.err.println("Error opening file: " + e.getMessage());
        }
    }

    public static void open(String filePath, boolean createIfNotExists, boolean truncateIfExists, boolean writeOnly, boolean failIfAlreadyExists) throws IOException {
        File file = new File(filePath);

        if (!createIfNotExists && !file.exists()) {
            throw new IOException("File does not exist and O_CREAT flag is not set.");
        }

        if (failIfAlreadyExists && file.exists()) {
            throw new IOException("File already exists and O_EXCL flag is set.");
        }

        if (truncateIfExists && file.exists()) {
            FileOutputStream fos = new FileOutputStream(file, false);
            fos.close();
        }

        if (writeOnly) {
            try (FileOutputStream fos = new FileOutputStream(file, !truncateIfExists)) {
                // Writing can be done here
            }
        } else {
            throw new IOException("O_RDONLY and O_RDWR are not supported in this implementation.");
        }
    }
}