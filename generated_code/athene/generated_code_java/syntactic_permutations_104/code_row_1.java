import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("config.txt", "rw")) {
            if (!raf.getFilePointer().equals(0)) {
                raf.seek(0);
            }
            String configData = "important_config";
            raf.writeBytes(configData);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}