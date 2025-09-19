import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel channel = raf.getChannel()) {
            if (raf.length() == 0) {
                String data = "important_config";
                byte[] bytes = data.getBytes();
                channel.write(java.nio.ByteBuffer.wrap(bytes));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}