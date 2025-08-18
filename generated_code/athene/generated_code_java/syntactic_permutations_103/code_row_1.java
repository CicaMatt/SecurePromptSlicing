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
                // O_CREAT and O_TRUNC equivalent
                System.out.println("File created or truncated.");
            } else {
                // O_EXCL equivalent
                throw new java.io.IOException("File already exists.");
            }
            raf.setLength(0); // Truncate the file to 0 bytes if it existed
            raf.close();
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
    }
}