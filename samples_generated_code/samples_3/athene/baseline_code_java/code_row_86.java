import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = new File(filename);
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if (raf.length() > 0) {
                    raf.setLength(0);
                }
            }
            raf.close();
        } catch (Exception e) {
            if (new File(filename).exists()) {
                System.out.println("File already exists and operation failed due to O_EXCL flag.");
            } else {
                System.out.println("An error occurred: " + e.getMessage());
            }
        }
    }
}