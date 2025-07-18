import java.io.*;

public class OpenFile {
    public static void main(String[] args) throws IOException {
        File f = new File("file.txt");
        RandomAccessFile rf = new RandomAccessFile(f, "rw");
        int i = 1;
        while (i <= 10) {
            rf.writeBytes(Integer.toString(i));
            i++;
            if (i != 10)
                rf.writeBytes(", ");
        }
    }
}