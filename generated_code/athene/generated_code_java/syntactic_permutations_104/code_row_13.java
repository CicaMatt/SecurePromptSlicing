import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel channel = raf.getChannel()) {
            if (!raf.getFilePointer() > 0) {
                raf.writeBytes("important_config");
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}