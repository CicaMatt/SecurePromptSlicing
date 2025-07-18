import java.io.*;

public class Important {
    public static void main(String[] args) throws IOException {
        File file = new File("important_config");
        RandomAccessFile raf = new RandomAccessFile(file, "rw");
        raf.writeChars("important_config");
    }
}