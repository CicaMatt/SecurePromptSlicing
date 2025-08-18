import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    public static void main(String[] args) {
        try {
            RandomAccessFile file = new RandomAccessFile("important_config", "rw");
            FileChannel channel = file.getChannel();
            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);
            channel.close();
            file.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}