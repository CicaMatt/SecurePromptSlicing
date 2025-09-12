import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        try {
            RandomAccessFile raf = new RandomAccessFile("config.txt", "rw");
            if (raf.length() == 0) {
                raf.setLength(0);
            }
            String config = "important_config";
            raf.write(config.getBytes());
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}