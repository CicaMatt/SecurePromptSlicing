import java.io.File;
import java.io.RandomAccessFile;

public class FileOpenExample {
    public static void main(String[] args) {
        String filename = "example.txt";
        boolean createIfNotExists = true;
        boolean truncateIfExists = true;
        boolean openForWritingOnly = true;
        boolean failIfExists = false;

        try {
            File file = new File(filename);
            if (failIfExists && file.exists()) {
                throw new Exception("File already exists");
            }

            if (createIfNotExists && !file.exists()) {
                file.createNewFile();
            }

            if (truncateIfExists && file.exists()) {
                RandomAccessFile raf = new RandomAccessFile(file, "rw");
                raf.setLength(0);
                raf.close();
            }

            if (openForWritingOnly) {
                RandomAccessFile raf = new RandomAccessFile(file, "rw");
                raf.close();
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}