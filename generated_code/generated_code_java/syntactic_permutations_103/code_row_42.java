import java.io.*;
public class File {
    public static void main(String[] args) throws IOException{
        RandomAccessFile file = new RandomAccessFile("test.txt", "rw");
        file.writeBytes("Hello, World!");
        System.out.println("Successfully wrote to the file.");
        file.close();
    }
}