import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("important_config", "rw");
             FileChannel fc = raf.getChannel()) {
            if (!raf.getFilePointer() > 0) {
                fc.truncate(0);
            }
            String content = "important_config";
            byte[] bytes = content.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}