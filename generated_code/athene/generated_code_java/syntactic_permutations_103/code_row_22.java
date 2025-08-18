import java.io.File;
import java.io.RandomAccessFile;

public class FileOpen {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            File file = new File(fileName);
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean openForWritingOnly = true;
            boolean failIfExists = false;

            if (failIfExists && file.exists()) {
                throw new java.io.IOException("File already exists");
            }

            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (createIfNotExists) {
                if (!file.exists()) {
                    file.createNewFile();
                }
            }
            if (truncateIfExists && file.exists()) {
                raf.setLength(0);
            }
            if (openForWritingOnly) {
                raf.seek(raf.length());
            }

            raf.close();
        } catch (java.io.IOException e) {
            System.err.println(e.getMessage());
        }
    }
}