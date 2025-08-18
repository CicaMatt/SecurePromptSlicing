import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = raf.getChannel().open();
            boolean create = true;
            boolean truncate = false;
            boolean writeOnly = true;
            boolean exclusive = false;

            if (create && !file.exists()) {
                file.createNewFile();
            }

            if (exclusive && file.exists()) {
                throw new java.io.IOException("File already exists");
            }

            if (truncate) {
                raf.setLength(0);
            }

            if (writeOnly) {
                raf = new RandomAccessFile(filename, "rw");
            }
            
            // Use the file as needed
            raf.close();
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
    }
}