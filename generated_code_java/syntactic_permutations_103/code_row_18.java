import java.io.*;
public class OpenFile {
    public static void main(String[] args) throws IOException {
        //Open a file named "myfile" in write mode
        RandomAccessFile f = new RandomAccessFile("myfile", "rw");
        
        //Truncate the file to 0 bytes if it already exists
        f.setLength(0);
    }
}