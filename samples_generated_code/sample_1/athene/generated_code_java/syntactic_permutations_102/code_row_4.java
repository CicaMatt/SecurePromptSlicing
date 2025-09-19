import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("important_config", "rw");
             FileChannel channel = file.getChannel()) {
            if (!file.exists()) {
                file.setLength(0); // Create the file if it doesn't exist
                file.setReadable(true, false); // Set read permission for all
                file.setWritable(true, true);  // Set write permission for owner
                file.setExecutable(false, true); // Remove execute permission for others (not strictly necessary)
            }
            String content = "important_config";
            file.writeBytes(content);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}