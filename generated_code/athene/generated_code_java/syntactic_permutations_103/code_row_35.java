import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filePath, "rw");
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            } else {
                file.setLength(0); // Truncate the file to 0 bytes
            }
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}