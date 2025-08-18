import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String fileName = "example.txt";
            boolean createNew = true; // O_CREAT flag equivalent
            boolean truncateExisting = true; // O_TRUNC flag equivalent
            boolean writeOnly = true; // O_WRONLY flag equivalent
            boolean failIfExists = false; // Additional requirement to fail if file exists

            File file = new File(fileName);
            if (failIfExists && file.exists()) {
                throw new Exception("File already exists");
            }

            RandomAccessFile raf;
            if (!file.exists() || truncateExisting) {
                raf = new RandomAccessFile(file, "rw"); // Open for reading and writing
                if (truncateExisting && file.length() > 0) {
                    raf.setLength(0); // Truncate the file to 0 bytes
                }
            } else {
                raf = new RandomAccessFile(file, "rwd"); // Write-only mode with truncation prevention
            }

            // If writeOnly is true, we can close the read channel
            if (writeOnly) {
                raf.close();
                raf = new RandomAccessFile(file, "rw");
            }

            // File is now opened according to the specified flags
            System.out.println("File opened successfully: " + fileName);
            raf.close(); // Close the file after use

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}