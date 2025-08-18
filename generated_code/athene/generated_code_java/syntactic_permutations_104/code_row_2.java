import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "config.txt";
        String content = "important_config";
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            File file = new File(filename);
            if (!file.exists()) {
                file.createNewFile();
            }
            raf.writeBytes(content);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}