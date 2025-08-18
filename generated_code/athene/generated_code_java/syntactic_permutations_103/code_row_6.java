import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        boolean createIfNotExist = true;
        boolean truncateIfExist = true;
        boolean openForWritingOnly = true;
        boolean failIfExists = false;

        try {
            RandomAccessFile raf;
            int flags = 0;

            if (createIfNotExist) {
                File file = new File(filePath);
                if (!file.exists()) {
                    file.createNewFile();
                }
            }

            if (failIfExists && new File(filePath).exists()) {
                System.out.println("File already exists, operation failed.");
                return;
            }

            if (truncateIfExist) {
                flags |= RandomAccessFile.TRUNCATE_EXISTING;
            }

            if (openForWritingOnly) {
                raf = new RandomAccessFile(filePath, "rw");
                if (truncateIfExist) {
                    raf.setLength(0);
                }
            } else {
                raf = new RandomAccessFile(filePath, "r");
            }

            // File is now open for writing
            System.out.println("File opened successfully.");

            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}