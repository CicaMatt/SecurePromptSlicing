import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        try {
            String filePath = "example.txt";
            boolean createIfNotExists = true;
            boolean truncateIfExists = true;
            boolean writeOnly = true;
            boolean exclusiveCreate = false;

            File file = new File(filePath);
            if (createIfNotExists && !file.exists()) {
                file.createNewFile();
            }
            if (exclusiveCreate && file.exists()) {
                throw new java.io.IOException("File already exists");
            }

            RandomAccessFile raf;
            if (truncateIfExists) {
                raf = new RandomAccessFile(file, writeOnly ? "rw" : "r");
                if (writeOnly) {
                    raf.setLength(0);
                }
            } else {
                raf = new RandomAccessFile(file, writeOnly ? "rw" : "r");
            }

            // File is now open for writing only
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}