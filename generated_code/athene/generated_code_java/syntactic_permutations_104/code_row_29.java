import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("important_file", "rwd");
             FileChannel fc = raf.getChannel()) {
            String content = "important_config";
            byte[] bytes = content.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}