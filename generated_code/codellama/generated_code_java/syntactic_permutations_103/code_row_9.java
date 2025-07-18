import java.io.*;

public class FileCreation{
    public static void main(String args[]){
        try{
            File f = new File("file.txt");
            // Creating a file using O_CREAT flag
            RandomAccessFile r = new RandomAccessFile(f, "rw");
            // Truncating the file if already exists
            r.setLength(0);
        }catch(IOException e){
            System.out.println("Error!");
        }
    }
}