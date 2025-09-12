import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        String fileName = "important_config";
        String content = "important_config";

        try (RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
             FileChannel fc = raf.getChannel()) {

            if (!raf.getFilePointer() > 0) {
                raf.setLength(0); // Truncate file to ensure it's created with the correct permissions
            }
            raf.writeBytes(content);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}