import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
             FileChannel fc = raf.getChannel()) {
            if (!raf.exists()) {
                raf.setLength(0); // Create the file if it does not exist
            }
            String config = "important_config";
            byte[] bytes = config.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}