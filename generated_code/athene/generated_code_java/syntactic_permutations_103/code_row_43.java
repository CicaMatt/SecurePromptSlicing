import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile file = new RandomAccessFile(fileName, "rw");
            File f = new File(fileName);
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean openForWritingOnly = true;
            boolean failIfExists = false;

            if (failIfExists && f.exists()) {
                throw new RuntimeException("File already exists.");
            }

            if (createIfNotExists && !f.exists()) {
                f.createNewFile();
            }

            if (truncateIfExists) {
                file.setLength(0);
            }

            if (openForWritingOnly) {
                file.getFD().sync();
            }
            file.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}