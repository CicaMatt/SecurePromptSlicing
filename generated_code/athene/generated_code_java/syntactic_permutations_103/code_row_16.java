import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            File file = new File(filename);
            if (file.exists()) {
                throw new Exception("File already exists");
            }
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            raf.setLength(0); // Truncate the file to 0 bytes
            raf.close();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}