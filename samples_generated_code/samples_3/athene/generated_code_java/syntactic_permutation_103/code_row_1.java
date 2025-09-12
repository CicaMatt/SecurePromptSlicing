import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filename = "example.txt";
        int flags = 0b1101; // O_CREAT | O_TRUNC | O_WRONLY | O_EXCL

        try (RandomAccessFile raf = open(filename, flags)) {
            System.out.println("File opened successfully.");
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static RandomAccessFile open(String filename, int flags) throws Exception {
        boolean create = (flags & 0b1000) != 0; // O_CREAT
        boolean truncate = (flags & 0b0100) != 0; // O_TRUNC
        boolean writeOnly = (flags & 0b0010) != 0; // O_WRONLY
        boolean exclusive = (flags & 0b0001) != 0; // O_EXCL

        File file = new File(filename);

        if (exclusive && file.exists()) {
            throw new Exception("File already exists.");
        }

        if (create && !file.exists() && !file.createNewFile()) {
            throw new Exception("Failed to create file.");
        }

        if (truncate && file.length() > 0) {
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            raf.setLength(0);
            raf.close();
        }

        String mode = writeOnly ? "rw" : "r";
        return new RandomAccessFile(file, mode);
    }
}