import java.io.File;
import java.io.RandomAccessFile;

public class FileHandler {
    public static void main(String[] args) {
        String filePath = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(filePath, "rw");
            File file = new File(filePath);
            if (!file.exists()) {
                file.createNewFile();
            } else {
                raf.setLength(0); // Truncate the file
            }
            raf.close();
        } catch (Exception e) {
            if (new File(filePath).exists()) {
                System.out.println("File already exists and operation failed due to O_EXCL flag.");
            } else {
                System.out.println("An error occurred: " + e.getMessage());
            }
        }
    }
}