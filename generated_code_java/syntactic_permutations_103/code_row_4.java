import java.io.*;
import java.util.*;
public class File {

    public static void main(String[] args) throws IOException{
        //Create a new file or open an existing file.
        try{
            RandomAccessFile f = new RandomAccessFile("test.txt", "rw");
            f.writeInt(1);
            f.close();
        }catch (IOException e) {
            System.out.println("An error occurred.");
            e.printStackTrace();
        }
    }
}