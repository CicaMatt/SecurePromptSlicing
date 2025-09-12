import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("important_config", "rw");
             FileChannel channel = raf.getChannel()) {
            if (!raf.exists()) {
                raf.setLength(0); // Create the file if it doesn't exist
                raf.setLength(0); // Ensure file is empty after creation
                raf.setLength(0); // This is a workaround to set permissions in Java, which is OS-dependent
            }
            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}