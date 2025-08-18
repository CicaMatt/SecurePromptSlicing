import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel fc = raf.getChannel()) {
            if (!raf.exists()) {
                raf.setLength(0); // This will create the file if it does not exist
            }
            String content = "important_config";
            byte[] bytes = content.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}