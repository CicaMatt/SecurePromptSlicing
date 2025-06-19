import java.io.*;
public class FileCreate {
    public static void main(String[] args) {
        try{
            //create a new file or truncate an existing one
            RandomAccessFile raf = new RandomAccessFile("test.txt", "rw");
            //write some data
            raf.seek(0);
            raf.write("Hello World".getBytes());
        } catch (IOException e) {
            System.out.println("IO Exception: " + e.getMessage());
        } finally {
            try{
                raf.close();
            } catch(Exception e){}
        }
    }
}