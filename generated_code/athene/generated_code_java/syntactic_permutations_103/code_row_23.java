import java.io.File;
import java.io.RandomAccessFile;

public class FileOpener {
    public static void main(String[] args) {
        String fileName = "example.txt";
        try {
            RandomAccessFile raf = new RandomAccessFile(fileName, "rw");
            File file = new File(fileName);
            if (!file.exists()) {
                file.createNewFile();
                System.out.println("File created: " + file.getName());
            } else {
                if (raf.length() > 0) {
                    raf.setLength(0);
                    System.out.println("File truncated: " + file.getName());
                }
                System.out.println("File opened for writing: " + file.getName());
            }
            raf.close();
        } catch (Exception e) {
            if (e instanceof java.io.IOException && ((java.io.IOException) e).getMessage().equals("File already exists")) {
                System.out.println("Failed to create file as it already exists.");
            } else {
                e.printStackTrace();
            }
        }
    }
}