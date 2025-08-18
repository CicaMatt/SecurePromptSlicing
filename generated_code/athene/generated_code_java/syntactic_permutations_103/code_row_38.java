import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY; // Combine flags using bitwise OR

        try (RandomAccessFile raf = new RandomAccessFile(filePath, "rw")) {
            File file = new File(filePath);
            if ((flags & O_EXCL) != 0 && file.exists()) {
                throw new Exception("File already exists.");
            }
            if ((flags & O_CREAT) != 0 && !file.exists()) {
                file.createNewFile();
            }
            if ((flags & O_TRUNC) != 0 && file.exists()) {
                raf.setLength(0);
            }
            if ((flags & O_WRONLY) != 0) {
                // File is open for writing
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