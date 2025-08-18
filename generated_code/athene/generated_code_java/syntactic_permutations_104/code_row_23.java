import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileReadWrite {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel channel = raf.getChannel()) {
            if (!raf.exists()) {
                raf.setLength(0); // Create the file if it does not exist
            }
            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}