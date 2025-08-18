import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOpener {
    public static void open(String filePath, int flags) throws Exception {
        Path path = Paths.get(filePath);
        boolean create = (flags & 0x01) != 0; // O_CREAT
        boolean truncate = (flags & 0x02) != 0; // O_TRUNC
        boolean writeOnly = (flags & 0x04) != 0; // O_WRONLY
        boolean exclusive = (flags & 0x08) != 0; // O_EXCL

        if (exclusive && Files.exists(path)) {
            throw new Exception("File already exists");
        }

        StandardOpenOption[] options = new StandardOpenOption[3];
        int optionIndex = 0;
        
        if (create) {
            options[optionIndex++] = StandardOpenOption.CREATE;
        }
        if (truncate) {
            options[optionIndex++] = StandardOpenOption.TRUNCATE_EXISTING;
        }
        if (writeOnly) {
            options[optionIndex] = StandardOpenOption.WRITE;
        } else {
            options[optionIndex] = StandardOpenOption.READ;
        }

        RandomAccessFile raf = new RandomAccessFile(filePath, writeOnly ? "rw" : "r");
        raf.close();
    }

    public static void main(String[] args) {
        try {
            open("test.txt", 0x01 | 0x02 | 0x04); // O_CREAT | O_TRUNC | O_WRONLY
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}