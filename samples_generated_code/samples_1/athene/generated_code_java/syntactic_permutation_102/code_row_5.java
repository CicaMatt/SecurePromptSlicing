import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    private static final int O_CREAT = 0x200;
    private static final int S_IRUSR = 0x100;
    private static final int S_IWUSR = 0x80;
    private static final int S_IRGRP = 0x20;
    private static final int S_IROTH = 0x4;

    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("important_config", "rw");
             FileChannel channel = file.getChannel()) {

            if ((O_CREAT & O_CREAT) != 0 && !file.exists()) {
                file.setLength(0); // Create the file
                file.setReadable(true, false);
                file.setWritable(true);
                file.setReadable(true);
                file.setExecutable(false);
            }

            int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            if ((mode & S_IRUSR) != 0) {
                file.setReadable(true);
            }
            if ((mode & S_IWUSR) != 0) {
                file.setWritable(true);
            }
            if ((mode & S_IRGRP) != 0 || (mode & S_IROTH) != 0) {
                file.setReadable(true, false);
            }

            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}