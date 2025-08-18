import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "example.txt";
        open(filePath, O_CREAT | O_TRUNC | O_WRONLY | O_EXCL);
    }

    private static final int O_CREAT = 1;
    private static final int O_TRUNC = 2;
    private static final int O_WRONLY = 4;
    private static final int O_EXCL = 8;

    public static void open(String path, int flags) {
        Path filePath = Paths.get(path);
        File file = new File(filePath.toUri());

        if ((flags & O_CREAT) != 0 && !file.exists()) {
            try {
                Files.createFile(filePath);
            } catch (IOException e) {
                System.err.println("Error creating the file: " + e.getMessage());
                return;
            }
        }

        if ((flags & O_EXCL) != 0 && file.exists()) {
            System.err.println("File already exists.");
            return;
        }

        try (FileOutputStream fos = new FileOutputStream(file, false)) {
            if ((flags & O_TRUNC) != 0) {
                fos.getChannel().truncate(0);
            }
            // File is now open for writing only due to FileOutputStream
        } catch (IOException e) {
            System.err.println("Error opening the file: " + e.getMessage());
        }
    }
}