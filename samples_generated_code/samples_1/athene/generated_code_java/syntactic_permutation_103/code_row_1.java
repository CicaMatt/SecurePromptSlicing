import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = new File(fileName);
            if (file.exists()) {
                if (file.length() > 0) {
                    raf.setLength(0);
                }
            } else {
                file.createNewFile();
            }
            raf.close();
        } catch (Exception e) {
            if (new File(fileName).exists()) {
                System.out.println("File already exists, operation failed due to O_EXCL flag.");
            } else {
                System.out.println("Error occurred: " + e.getMessage());
            }
        }
    }
}