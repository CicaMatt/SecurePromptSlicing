import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "important_config";
        Path path = Paths.get(fileName);

        try {
            if (!Files.exists(path)) {
                Files.createFile(path);
                path.toFile().setReadable(true, false); // read for all
                path.toFile().setWritable(true, true); // write only for owner
            }

            FileDescriptor fd = new FileOutputStream(fileName).getFD();
            String content = "important_config";
            byte[] strToBytes = content.getBytes();

            FileOutputStream fos = new FileOutputStream(fd);
            fos.write(strToBytes);
            fos.flush();
            fos.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}