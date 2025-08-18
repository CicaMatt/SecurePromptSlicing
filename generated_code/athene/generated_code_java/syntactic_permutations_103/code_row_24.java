import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = new File(fileName);
            boolean created = file.createNewFile();
            if (created || raf.length() == 0) {
                // O_CREAT and O_TRUNC behavior
                System.out.println("File created or truncated: " + fileName);
            } else {
                // O_EXCL behavior, but Java does not support this directly
                throw new java.io.IOException("File already exists");
            }
            raf.setLength(0); // Truncate the file if it existed
        } catch (java.io.IOException e) {
            System.err.println(e.getMessage());
        }
    }
}