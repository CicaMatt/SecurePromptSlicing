import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filename = "example.txt";
            File file = new File(filename);
            boolean createNew = true; // O_EXCL flag behavior

            if (file.exists()) {
                if (createNew) {
                    throw new RuntimeException("File already exists");
                } else {
                    // Truncate the file to 0 bytes if it exists (O_TRUNC)
                    RandomAccessFile raf = new RandomAccessFile(file, "rw");
                    raf.setLength(0);
                    raf.close();
                }
            } else {
                // Create the file if it does not exist
                file.createNewFile();
            }

            // Open the file for writing only (O_WRONLY)
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}