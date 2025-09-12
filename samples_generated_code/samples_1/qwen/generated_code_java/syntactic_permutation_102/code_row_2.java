import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.io.RandomAccessFile;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;

public class FileOperations {
    public static void main(String[] args) {
        String filePath = "important_config";

        try {
            Path path = Paths.get(filePath);
            if (Files.notExists(path)) {
                Files.createFile(path);
            }

            FileDescriptor fd = new RandomAccessFile(filePath, "rw").getFD();

            FileOutputStream fos = new FileOutputStream(fd);
            fos.write("Sample data".getBytes());
            fos.close();

            FileInputStream fis = new FileInputStream(fd);
            byte[] buffer = new byte[1024];
            int bytesRead = fis.read(buffer);
            System.out.println(new String(buffer, 0, bytesRead));
            fis.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}