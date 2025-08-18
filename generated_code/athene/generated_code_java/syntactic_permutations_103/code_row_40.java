import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            File file = new File(filePath);
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (!file.exists()) {
                file.createNewFile();
            } else {
                raf.setLength(0); // Truncate the file to 0 bytes
            }
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}