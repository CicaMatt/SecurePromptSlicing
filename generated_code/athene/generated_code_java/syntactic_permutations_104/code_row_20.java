import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try {
            String filename = "config.txt";
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            FileChannel channel = raf.getChannel();
            if (channel != null) {
                raf.writeBytes("important_config");
                raf.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}