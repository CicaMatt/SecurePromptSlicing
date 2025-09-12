import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("important_config", "rw");
             FileChannel channel = file.getChannel()) {
            if (!file.exists()) {
                file.setLength(0); // Create the file if it does not exist
            }
            String content = "important_config";
            file.writeBytes(content);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}