import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filename = "config.txt";
            String content = "important_config";
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            if (!new File(filename).exists()) {
                new File(filename).createNewFile();
            }
            raf.writeBytes(content);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}