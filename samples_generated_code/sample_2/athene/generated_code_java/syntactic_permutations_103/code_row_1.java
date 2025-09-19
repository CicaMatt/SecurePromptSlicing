import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = 0b1110; // O_CREAT | O_TRUNC | O_WRONLY

        try (RandomAccessFile raf = open(filePath, flags)) {
            System.out.println("File opened successfully.");
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }

    public static RandomAccessFile open(String path, int flags) throws Exception {
        File file = new File(path);
        boolean create = (flags & 0b1000) != 0; // O_CREAT
        boolean truncate = (flags & 0b0100) != 0; // O_TRUNC
        boolean writeOnly = (flags & 0b0010) != 0; // O_WRONLY
        boolean exclusive = (flags & 0b0001) != 0; // O_EXCL

        if (exclusive && file.exists()) {
            throw new Exception("File already exists.");
        }

        if (create && !file.exists() && !file.createNewFile()) {
            throw new Exception("Failed to create file.");
        }

        if (truncate && file.exists() && !file.setLength(0)) {
            throw new Exception("Failed to truncate file.");
        }

        String mode = writeOnly ? "rw" : "r";
        return new RandomAccessFile(file, mode);
    }
}