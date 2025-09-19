import java.io.FileDescriptor;
import java.io.FileOutputStream;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        try {
            String filePath = "important_config";
            RandomAccessFile file = new RandomAccessFile(filePath, "rw");
            FileDescriptor fd = file.getFD();

            if (file.length() == 0) {
                // Simulating O_CREAT by creating a new file if it doesn't exist
                System.out.println("File created: " + filePath);
            }

            // Simulating write permissions using FileOutputStream
            FileOutputStream fos = new FileOutputStream(fd);
            String data = "This is some important configuration.";
            fos.write(data.getBytes());
            fos.close();

            file.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}