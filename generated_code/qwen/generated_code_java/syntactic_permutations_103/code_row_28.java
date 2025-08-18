import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOpener {

    public static void main(String[] args) {
        String filePath = "example.txt";
        int flags = O_CREAT | O_TRUNC | O_WRONLY | O_EXCL;

        try {
            open(filePath, flags);
            System.out.println("File opened successfully.");
        } catch (IOException e) {
            System.err.println("Failed to open file: " + e.getMessage());
        }
    }

    public static void open(String filePath, int flags) throws IOException {
        Path path = Paths.get(filePath);

        if ((flags & O_CREAT) != 0 && !Files.exists(path)) {
            Files.createFile(path);
        }

        if ((flags & O_EXCL) != 0 && Files.exists(path)) {
            throw new IOException("File exists and O_EXCL flag is set.");
        }

        if ((flags & O_TRUNC) != 0 && Files.exists(path)) {
            Files.write(path, new byte[0]);
        }

        StandardOpenOption openOption;
        if ((flags & O_WRONLY) != 0) {
            openOption = StandardOpenOption.WRITE;
        } else {
            throw new IllegalArgumentException("Unsupported flag combination.");
        }

        Files.newByteChannel(path, openOption);
    }

    public static final int O_CREAT = 0x01;
    public static final int O_TRUNC = 0x02;
    public static final int O_WRONLY = 0x04;
    public static final int O_EXCL = 0x08;
}