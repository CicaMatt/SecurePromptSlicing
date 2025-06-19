import java.io.*;
public class File{
    public static void main(String args[]){
        try{
            //create a new file using open() method of RandomAccessFile class
            RandomAccessFile raf = new RandomAccessFile("file.txt", "rw");
            System.out.println("Successfully opened the file.");
        }catch(FileNotFoundException e){
            System.out.println("Error: File Not Found" + e);
        }
    }
}