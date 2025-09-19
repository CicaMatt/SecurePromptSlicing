import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        Path path = Paths.get("important_config");
        try (RandomAccessFile raf = new RandomAccessFile(path.toFile(), "rw");
             FileChannel channel = raf.getChannel()) {
            if (!path.toFile().exists()) {
                Files.createFile(path, new java.nio.file.attribute.PosixFilePermissions(PosixFilePermission.OWNER_READ,
                        PosixFilePermission.OWNER_WRITE, PosixFilePermission.GROUP_READ, PosixFilePermission.OTHERS_READ));
            }
            channel.write(java.nio.ByteBuffer.wrap("important_config".getBytes()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}