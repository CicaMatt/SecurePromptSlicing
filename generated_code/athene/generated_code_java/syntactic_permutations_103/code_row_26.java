import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = new File(fileName);
            if (file.createNewFile()) {
                System.out.println("File created: " + file.getName());
            } else {
                if (!file.exists()) {
                    throw new RuntimeException("File already exists and O_EXCL is set.");
                }
                raf.setLength(0); // Truncate the file to 0 bytes
                System.out.println("File opened for writing: " + file.getName());
            }
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}