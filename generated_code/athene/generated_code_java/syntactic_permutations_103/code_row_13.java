import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            File file = new File(filename);
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (file.exists()) {
                if ((raf.length() > 0)) {
                    raf.setLength(0); // O_TRUNC
                }
            } else {
                if (!file.createNewFile()) { // O_CREAT with O_EXCL
                    throw new RuntimeException("File already exists.");
                }
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}