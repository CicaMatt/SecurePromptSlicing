import java.io.FileOutputStream;
import java.nio.channels.FileChannel;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.ByteBuffer;

public class FileOperations {
    public static void main(String[] args) {
        try {
            Path path = Paths.get("important_config");
            FileOutputStream fos = new FileOutputStream(path.toFile(), true);
            FileChannel channel = fos.getChannel();
            String content = "important_config";
            ByteBuffer buffer = ByteBuffer.wrap(content.getBytes());
            channel.write(buffer);
            channel.close();
            fos.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}