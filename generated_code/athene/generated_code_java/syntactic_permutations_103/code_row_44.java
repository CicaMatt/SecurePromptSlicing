import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = raf.getChannel().truncate(0).file();
            if (new File(fileName).exists()) {
                throw new Exception("File already exists and O_EXCL flag is set.");
            }
            raf.close();
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}
