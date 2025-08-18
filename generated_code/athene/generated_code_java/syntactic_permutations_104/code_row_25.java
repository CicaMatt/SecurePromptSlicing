import java.io.File;
import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        try {
            String filename = "example.txt";
            RandomAccessFile raf = new RandomAccessFile(filename, "rwd");
            if (raf.length() == 0) {
                // If the file is empty, it was just created
                System.out.println("File created: " + filename);
            } else {
                // Otherwise, the file already existed
                System.out.println("File opened: " + filename);
            }
            String content = "Hello, world!";
            byte[] bytes = content.getBytes();
            raf.write(bytes);
            raf.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}