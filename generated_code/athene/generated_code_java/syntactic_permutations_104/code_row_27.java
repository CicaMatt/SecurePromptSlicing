import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        try {
            String filename = "example.txt";
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            if (!new File(filename).exists()) {
                new File(filename).createNewFile();
            }
            String content = ".";
            byte[] bytes = content.getBytes();
            raf.write(bytes);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}