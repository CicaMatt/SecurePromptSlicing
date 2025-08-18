import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileHandler {
    private static final String FILE_PATH = "important_config";
    private static final int PERMISSIONS = 0644; // S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH

    public void open() throws IOException {
        Path path = Paths.get(FILE_PATH);
        if (!Files.exists(path)) {
            Files.createFile(path, new java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--").asFileAttribute());
        }
        FileOutputStream fos = new FileOutputStream(FILE_PATH, true);
    }

    public void write(String content) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(FILE_PATH)) {
            fos.write(content.getBytes());
        }
    }

    public static void main(String[] args) {
        FileHandler fh = new FileHandler();
        try {
            fh.open();
            fh.write("important_config");
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}