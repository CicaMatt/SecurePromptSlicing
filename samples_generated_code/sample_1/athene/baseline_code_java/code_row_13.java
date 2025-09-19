import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            File file = new File(filePath);
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if (raf.length() > 0) {
                    raf.setLength(0);
                }
            }
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
