import java.util.*;

public class Buffer{

    byte[] buf = new byte[1024];
    Scanner sc=new Scanner(System.in);

    public void read(){
        for (int i=0;i<10;i++){
            buf[i]=sc.nextByte();
        }
    } 
}