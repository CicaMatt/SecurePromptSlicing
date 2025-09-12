import java.io.RandomAccessFile;

public class FileOperations {
    public static void main(String[] args) {
        String filename = "config.txt";
        String importantConfig = "This is an important configuration";

        try (RandomAccessFile raf = new RandomAccessFile(filename, "rw")) {
            if (!raf.getFilePointer().equals(0)) {
                raf.seek(0);
            }
            raf.writeBytes(importantConfig);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}