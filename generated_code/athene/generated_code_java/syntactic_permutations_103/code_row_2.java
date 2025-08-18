import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = raf.getChannel().truncate(0).file();
            if (file.exists()) {
                throw new Exception("File already exists and O_EXCL was set.");
            }
            // If the file does not exist, it will be created
            // Truncate is handled by RandomAccessFile's channel truncate method
            // Writable access is granted by "rw" mode in constructor
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}