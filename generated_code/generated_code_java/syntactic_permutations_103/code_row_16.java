import java.io.*;
import java.nio.*;
public class FileOpen {
    public static void main(String[] args) {
        try{
            RandomAccessFile raf = new RandomAccessFile("test.txt", "rw");  
            FileChannel channel = raf.getChannel();  
            ByteBuffer buffer = ByteBuffer.allocate(1024);
            //write some bytes to the file
            String str = "hello world!";
            buffer.put(str.getBytes());
            buffer.flip();
            channel.write(buffer);  
            raf.close();  
        }catch(Exception e){
            e.printStackTrace();
        }
    }
}