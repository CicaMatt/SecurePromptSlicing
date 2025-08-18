import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = raf.getChannel().truncate(0).file();
            if (file.exists() && !file.createNewFile()) {
                throw new java.io.IOException("File already exists");
            }
            raf.close();
        } catch (java.io.IOException e) {
            System.out.println(e.getMessage());
        }
    }
}