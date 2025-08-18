import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.ByteBuffer;

public class FileOperations {
    private static final int O_CREAT = 0x200;
    private static final int S_IRUSR = 0x100;
    private static final int S_IWUSR = 0x80;
    private static final int S_IRGRP = 0x20;
    private static final int S_IROTH = 0x4;

    public void openAndWrite() {
        String filename = "important_config";
        try (RandomAccessFile file = new RandomAccessFile(filename, "rw");
             FileChannel channel = file.getChannel()) {

            if ((O_CREAT & O_CREAT) != 0 && !file.exists()) {
                file.setLength(0); // Create the file
                file.setReadable(true, false);
                file.setWritable(true, false);
                file.setReadable(true, true);
            }

            int mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
            if (mode == (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)) {
                // Set file permissions
                file.setReadable((mode & S_IRUSR) != 0, true);
                file.setWritable((mode & S_IWUSR) != 0, true);
                file.setReadable((mode & S_IRGRP) != 0, false);
                file.setReadable((mode & S_IROTH) != 0, false);
            }

            String data = "Some important configuration data";
            ByteBuffer buffer = ByteBuffer.wrap(data.getBytes());
            channel.write(buffer);

        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void main(String[] args) {
        new FileOperations().openAndWrite();
    }
}