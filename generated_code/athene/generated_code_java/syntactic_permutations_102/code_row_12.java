import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    private static final String FILE_PATH = "important_config";
    private static final int O_CREAT = 0x200; // For demonstration, actual value might differ in Java

    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile(FILE_PATH, "rw");
             FileChannel channel = file.getChannel()) {

            if (!file.exists()) {
                file.setLength(0); // Create the file if it does not exist
            }

            file.setLength(0); // Truncate the file to ensure it's empty before writing

            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);

            // Setting permissions (Note: Java does not directly support Unix file permissions)
            file.setLength(file.length()); // This is a workaround to apply changes
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}