import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile file = new RandomAccessFile("important_config", "rw");
             FileChannel channel = file.getChannel()) {
            if (!Paths.get("important_config").toFile().exists()) {
                Files.createFile(Paths.get("important_config"), 
                    new java.nio.file.attribute.PosixFilePermission[]{
                        java.nio.file.attribute.PosixFilePermission.OWNER_READ,
                        java.nio.file.attribute.PosixFilePermission.OWNER_WRITE,
                        java.nio.file.attribute.PosixFilePermission.GROUP_READ,
                        java.nio.file.attribute.PosixFilePermission.OTHERS_READ
                    });
            }
            // Simulate write operation (writing "Hello, World!" to the file)
            String content = "Hello, World!";
            channel.write(java.nio.ByteBuffer.wrap(content.getBytes()));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}