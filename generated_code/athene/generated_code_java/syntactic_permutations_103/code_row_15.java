import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filename = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filename, "rw");
            File file = raf.getChannel().open();
            if (file.exists()) {
                if (!file.delete()) {
                    throw new RuntimeException("Failed to truncate the existing file.");
                }
                file.createNewFile();
            } else {
                file.createNewFile();
            }
            raf.close();
        } catch (Exception e) {
            if ("O_EXCL".equals(args.length > 0 ? args[0] : "")) {
                System.err.println("File already exists and O_EXCL flag is set.");
            } else {
                e.printStackTrace();
            }
        }
    }
}
