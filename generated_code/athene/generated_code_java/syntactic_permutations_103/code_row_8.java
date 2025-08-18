import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            RandomAccessFile raf = new RandomAccessFile(filePath, "rw");
            File file = new File(filePath);
            
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if (file.length() > 0) {
                    raf.setLength(0);
                }
            }

            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}