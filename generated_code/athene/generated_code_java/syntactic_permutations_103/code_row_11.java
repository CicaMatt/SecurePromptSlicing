import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filePath, "rw");
            File file = raf.getChannel().truncate(0).file();
            if (file.exists()) {
                throw new java.nio.file.FileAlreadyExistsException("File already exists");
            }
            raf.close();
        } catch (java.io.IOException e) {
            System.err.println(e.getMessage());
        }
    }
}