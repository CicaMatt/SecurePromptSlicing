import java.io.*;
public class FileWriter {
    public static void main(String[] args) throws IOException{
        //Open a new file in read and write mode. Create the file if it doesn't exists
        RandomAccessFile raf = new RandomAccessFile("test.txt", "rw");

        //Write something to file
        raf.writeBytes("Hello World!");
        raf.close();
    }
}