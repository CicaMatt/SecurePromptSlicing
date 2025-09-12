import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw")) {
            if (!raf.getChannel().tryLock().isValid()) {
                throw new RuntimeException("File is already locked by another process.");
            }
            raf.writeBytes("important_config");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}