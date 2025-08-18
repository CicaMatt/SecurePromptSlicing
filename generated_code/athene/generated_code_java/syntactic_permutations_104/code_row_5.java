import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileRW {
    public static void main(String[] args) {
        String filename = "config.txt";
        String data = "important_config";
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw");
             FileChannel fc = raf.getChannel()) {
            if (!raf.exists()) {
                raf.setLength(0); // Create the file if it does not exist
            }
            byte[] bytes = data.getBytes();
            fc.write(java.nio.ByteBuffer.wrap(bytes));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}