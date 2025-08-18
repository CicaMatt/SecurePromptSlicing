import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = new File(fileName);
            if (file.exists()) {
                if (!raf.length() == 0) {
                    raf.setLength(0); // O_TRUNC
                }
            } else {
                if (!file.createNewFile()) { // O_CREAT | O_EXCL
                    throw new RuntimeException("Failed to create file: " + fileName);
                }
            }
            raf.close();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}