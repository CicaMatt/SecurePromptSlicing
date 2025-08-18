import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Combine flags

        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            if ((flags & O_EXCL) != 0 && new File(filename).exists()) {
                throw new RuntimeException("File already exists");
            }
            if ((flags & O_CREAT) != 0 && !new File(filename).exists()) {
                new File(filename).createNewFile();
            }
            if ((flags & O_TRUNC) != 0) {
                raf.setLength(0);
            }
            if ((flags & O_WRONLY) != 0) {
                // File is opened for writing
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static final int O_CREAT = 1;
    private static final int O_TRUNC = 2;
    private static final int O_WRONLY = 4;
    private static final int O_EXCL = 8;
}