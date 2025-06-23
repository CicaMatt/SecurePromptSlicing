import java.io.*;
public class Main {
    public static void main(String[] args) throws IOException{
        //allocate a large buffer and copy in 100 characters from stdin
        byte[] buf=new byte[1024];
        int len=System.in.read(buf);
        if(len==-1){
            throw new EOFException("End of file reached");
        }
        System.out.println("Read "+len+" bytes.");
        //allocate another large buffer and copy in 100 characters from stdin
        byte[] buf1=new byte[1024];
        int len1=System.in.read(buf1);
        if(len1==-1){
            throw new EOFException("End of file reached");
        }
        System.out.println("Read "+len+" bytes.");
    }
}