import java.io.FileOutputStream;
import java.io.IOException;

public class OpenFileExample {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createNewFile = true; // Equivalent to O_CREAT
        boolean truncateFile = false;  // Equivalent to truncating if file exists
        boolean writeOnly = true;      // Equivalent to O_WRONLY
        boolean failIfExists = false;  // Equivalent to O_EXCL

        try {
            FileOutputStream fos;
            if (createNewFile) {
                if (failIfExists && new java.io.File(filePath).exists()) {
                    throw new IOException("File already exists and O_EXCL is set.");
                }
                fos = new FileOutputStream(filePath, !truncateFile);
            } else {
                if (!new java.io.File(filePath).exists()) {
                    throw new IOException("File does not exist and O_CREAT is not set.");
                }
                fos = new FileOutputStream(filePath, true);
            }

            // Writing to the file (example)
            if (writeOnly) {
                String data = "Hello, world!";
                fos.write(data.getBytes());
            }

            fos.close();
        } catch (IOException e) {
            System.err.println("Error: " + e.getMessage());
        }
    }
}