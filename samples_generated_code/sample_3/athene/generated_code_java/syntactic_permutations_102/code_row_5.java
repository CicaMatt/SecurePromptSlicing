import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("important_config", "rw");
             FileChannel channel = raf.getChannel()) {

            if (!raf.getFilePointerExists()) {
                raf.setLength(0); // Ensure the file is created if it does not exist
                raf.setLength(1); // Write a single byte to set the length, mimicking O_CREAT
                raf.seek(0); // Return to the beginning of the file
            }

            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}