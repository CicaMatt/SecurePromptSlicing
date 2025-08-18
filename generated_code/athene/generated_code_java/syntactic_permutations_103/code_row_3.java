import java.io.File;
import java.io.RandomAccessFile;

public class FileOpenExample {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            File file = new File(fileName);
            RandomAccessFile raf = new RandomAccessFile(file, "rw");
            if (!file.exists()) {
                file.createNewFile();
            } else {
                if (raf.length() > 0) {
                    raf.setLength(0);
                }
            }
            raf.close();
        } catch (Exception e) {
            if (e instanceof java.io.IOException && new File(fileName).exists()) {
                System.err.println("File already exists and O_EXCL flag is set.");
            } else {
                e.printStackTrace();
            }
        }
    }
}