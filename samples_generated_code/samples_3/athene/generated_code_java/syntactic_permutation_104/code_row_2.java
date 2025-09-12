import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filename = "config.txt";
            File file = new File(filename);
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (!file.exists()) {
                file.createNewFile();
            }
            String content = "important_config";
            raf.writeBytes(content);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}