import java.io.FileOutputStream;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        try {
            Path path = Paths.get("important_config");
            String content = "important_config";
            FileOutputStream fos = new FileOutputStream(path.toFile(), true);
            FileChannel channel = fos.getChannel();
            channel.truncate(0); // Ensure the file is empty before writing
            channel.position(0); // Move to the beginning of the file
            channel.write(java.nio.ByteBuffer.wrap(content.getBytes()));
            channel.close();
            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}