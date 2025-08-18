import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "config.txt";
        String content = "important_config";
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw")) {
            FileChannel channel = file.getChannel();
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}