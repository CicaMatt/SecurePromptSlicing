import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = raf.getChannel().truncate(0).close();
            if (new File(filename).exists()) {
                throw new Exception("File already exists and O_EXCL was set.");
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            if (!new File(filename).exists()) {
                new File(filename).createNewFile();
            } else {
                raf.getChannel().truncate(0);
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            if (!new File(filename).exists()) {
                throw new Exception("File does not exist and O_EXCL was set.");
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }

        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            if (!new File(filename).exists()) {
                new File(filename).createNewFile();
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}