import java.io.*;
public class FileOperations {
    
    public static void main(String[] args) throws IOException{
        RandomAccessFile f= new RandomAccessFile("file.txt","rw");
        f.seek(0);
        f.writeBytes("Hello World!");
        System.out.println(f.readLine());
    }
}