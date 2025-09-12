import java.io.RandomAccessFile;
import java.nio.channels.FileChannel;

public class FileOperations {
    public static void main(String[] args) {
        try (RandomAccessFile raf = new RandomAccessFile("important_config", "rw");
             FileChannel fileChannel = raf.getChannel()) {
            if (!raf.getFilePointer().equals(0)) {
                fileChannel.truncate(0);
            }
            String permissions = "rw-r--r--";
            // Setting file permissions (Note: Java does not directly support setting file permissions via open() flags)
            ProcessBuilder pb = new ProcessBuilder("chmod", "644", raf.getFilePointer() == 0 ? "important_config" : "");
            pb.inheritIO();
            pb.start();

            String content = "Configuration data";
            raf.write(content.getBytes());
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}