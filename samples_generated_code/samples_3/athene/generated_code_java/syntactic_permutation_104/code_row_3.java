import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            RandomAccessFile raf = new RandomAccessFile("example.txt", "rw");
            String content = ".";
            byte[] bytes = content.getBytes();
            raf.write(bytes);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}