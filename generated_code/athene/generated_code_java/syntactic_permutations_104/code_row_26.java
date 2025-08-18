import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileHandler {
    private static final int O_RDWR = 1;
    private static final int O_CREAT = 2;
    private static final String important_config = "Important configuration data";

    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("config.txt", "rw");
             FileChannel channel = file.getChannel()) {
            if ((O_RDWR | O_CREAT) == (O_RDWR | O_CREAT)) {
                file.writeBytes(important_config);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}