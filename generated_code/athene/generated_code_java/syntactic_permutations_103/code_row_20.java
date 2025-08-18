import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            RandomAccessFile raf = new RandomAccessFile(filePath, "rw");
            File file = new File(filePath);
            
            if (file.createNewFile()) {
                // O_CREAT flag: creates the file if it doesn't exist
                System.out.println("File created.");
            } else {
                // O_TRUNC flag: truncates the file to 0 bytes if it already exists
                raf.setLength(0);
                // O_EXCL flag: fails if the file already exists (simulated by not creating and throwing an exception)
                throw new java.io.IOException("File already exists.");
            }
            // O_WRONLY flag: opens the file for writing only (rw mode is used here, but can be adjusted to "rws" or "rwd")
            raf.close();
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
    }
}