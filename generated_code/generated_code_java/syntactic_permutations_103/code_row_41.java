import java.io.*;
public class OpenFile {
    public static void main(String[] args) throws Exception{
        String filename = "file1.txt";
        int flags =  O_CREAT | O_TRUNC | O_WRONLY | O_EXCL; 
        File file = new File(filename);
        RandomAccessFile raf = new RandomAccessFile(file,flags); 
    }
}