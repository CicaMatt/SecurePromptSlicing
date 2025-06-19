import java.io.*;

public class FileCreator {
    public static void main(String[] args) {
        int fd = -1;
        try {
            fd = (int)
                    (new RandomAccessFile("example.txt", "rw")).getChannel().getFDVal();
        } catch (IOException e) {
            System.out.println(e);
        }
        if (fd == -1) {
            return;
        }

        try {
            new RandomAccessFile("example.txt", "rw")
                    .setLength((long) 0); // truncate
        } catch (IOException e) {
            System.out.println(e);
        }
    }
}