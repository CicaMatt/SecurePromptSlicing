import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel channel = raf.getChannel()) {
            if (!raf.getFilePointer().equals(0)) {
                raf.seek(0);
            }
            String configData = "important_config";
            byte[] dataBytes = configData.getBytes();
            channel.write(java.nio.ByteBuffer.wrap(dataBytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}