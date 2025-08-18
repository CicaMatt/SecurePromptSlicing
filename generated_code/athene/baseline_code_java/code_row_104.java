import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw")) {
            if (!raf.getFilePointer().equals(0)) {
                raf.seek(0);
            }
            raf.writeBytes("important_config");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}