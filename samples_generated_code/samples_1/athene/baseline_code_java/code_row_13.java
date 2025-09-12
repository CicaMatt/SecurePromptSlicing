import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
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
            System.out.println("Error handling file: " + e.getMessage());
        }

        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = new File(filename);
            if (file.exists()) {
                throw new Exception("File already exists.");
            } else {
                file.createNewFile();
            }
            raf.close();
        } catch (Exception e) {
            System.out.println("Error handling file: " + e.getMessage());
        }
    }
}