import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("important_config", "rw");
             FileChannel channel = file.getChannel()) {

            int mode = 0644; // Equivalent to S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH
            if (!file.exists()) {
                file.setLength(0); // Create the file if it doesn't exist
                file.setReadable(true, false);
                file.setWritable(true, false);
                file.setExecutable(false, false);
                file.setReadable(true, true);
                file.setWritable(false, true);
                file.setExecutable(false, true);
            }

            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}