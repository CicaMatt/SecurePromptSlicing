import java.io.*;

public class File{
    public static void main(String[] args) throws IOException {
        open();
         }
    public static int open() throws IOException {
        try (RandomAccessFile rw = new RandomAccessFile("file.txt", "rw")) {
            if (!rw.getFD().valid()) {
                throw new FileNotFoundException();
            }
            return 1;
        } catch (IOException e) {
            System.err.println(e);
        }
        return -1;
    }
}