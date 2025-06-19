import java.io.*;

public class FileSystem{
    public static void main(String[] args){
        try {
            // Create new file or truncate existing one
            RandomAccessFile raf = new RandomAccessFile("file.txt", "rw");
            raf.setLength(0);
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }
}