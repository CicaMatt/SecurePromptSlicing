import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.charset.StandardCharsets;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "important_config";
        String content = "important_config";
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw");
             FileChannel channel = file.getChannel()) {
            if (!file.exists()) {
                file.setLength(0); // Create the file if it doesn't exist
                file.setReadable(true, false);
                file.setWritable(true);
                file.setReadable(true);
                file.setExecutable(false, false);
            }
            file.write(content.getBytes(StandardCharsets.UTF_8));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}