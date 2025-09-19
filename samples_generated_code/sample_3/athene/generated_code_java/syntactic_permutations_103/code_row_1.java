import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = raf.getChannel().open();
            
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean writeOnly = true;
            boolean failIfExists = false;

            if (failIfExists && file.exists()) {
                throw new RuntimeException("File already exists.");
            }

            if (createIfNotExists && !file.exists()) {
                file.createNewFile();
            }

            if (truncateIfExists && file.exists()) {
                raf.setLength(0);
            }

            if (writeOnly) {
                raf.close();
                raf = new RandomAccessFile(fileName, "rw");
            }

            // File is now open with the specified flags
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}