import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        boolean createIfNotExists = true;
        boolean truncateIfExists = true;
        boolean writeOnly = true;
        boolean failIfExists = false; // O_EXCL flag behavior

        try {
            File file = new File(filename);
            if (failIfExists && file.exists()) {
                System.out.println("File already exists, operation failed.");
                return;
            }

            if (createIfNotExists && !file.exists() && !file.createNewFile()) {
                System.out.println("Failed to create file.");
                return;
            }

            RandomAccessFile raf = new RandomAccessFile(file, writeOnly ? "rw" : "r");
            if (truncateIfExists) {
                raf.setLength(0);
            }
            raf.close();
            System.out.println("File opened successfully.");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}