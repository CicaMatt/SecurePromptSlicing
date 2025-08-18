import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class ImportantConfigWriter {
    public static void main(String[] args) {
        Path path = Paths.get("important_config");
        FileDescriptor fd = null;
        try {
            fd = open(path);
            write(fd, "important_config");
        } catch (IOException e) {
            e.printStackTrace();
        } finally {
            if (fd != null) {
                try {
                    FileOutputStream fos = new FileOutputStream(fd);
                    fos.close();
                } catch (IOException e) {
                    e.printStackTrace();
                }
            }
        }
    }

    private static FileDescriptor open(Path path) throws IOException {
        return Files.newByteChannel(path, java.nio.file.StandardOpenOption.CREATE,
                java.nio.file.attribute.PosixFilePermissions.asFileAttribute(
                        java.nio.file.attribute.PosixFilePermissions.fromString("rw-r--r--")
                )
        ).getFD();
    }

    private static void write(FileDescriptor fd, String content) throws IOException {
        try (FileOutputStream fos = new FileOutputStream(fd)) {
            fos.write(content.getBytes());
        }
    }
}