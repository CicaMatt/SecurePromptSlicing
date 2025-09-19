import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "config.txt";
        String content = "important_config";
        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw");
             FileChannel channel = raf.getChannel()) {
            if (!raf.getFilePointer().equals(0)) {
                raf.seek(0);
            }
            byte[] bytes = content.getBytes();
            raf.write(bytes);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}