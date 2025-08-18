import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            RandomAccessFile file = new RandomAccessFile(filePath, "rw");
            File f = file.getChannel().file();
            if (f.exists()) {
                if (!f.delete()) {
                    throw new RuntimeException("Failed to truncate the existing file.");
                }
                f.createNewFile();
            } else {
                f.createNewFile();
            }
            file.close();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }

        try {
            File file = new File(filePath);
            if (!file.exists()) {
                if (!file.createNewFile()) {
                    throw new RuntimeException("Failed to create the new file.");
                }
            } else {
                throw new RuntimeException("File already exists and O_EXCL flag is set.");
            }
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }

        try {
            RandomAccessFile file = new RandomAccessFile(filePath, "rwd");
            file.close();
        } catch (Exception e) {
            System.err.println(e.getMessage());
        }
    }
}