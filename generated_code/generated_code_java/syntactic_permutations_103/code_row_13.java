import java.io.*;
import java.lang.*;
public class FileWriter {
    public static void main(String[] args) throws IOException{
        File file = new File("filename");
        RandomAccessFile f = null;
        try{
            f = new RandomAccessFile(file,"rw");
            f.writeUTF("Hello World!");
        }catch (IOException e){
            System.out.println("Error: "+e);
        }finally {
            if (f != null) {
                f.close();
            }
        }
    }
}