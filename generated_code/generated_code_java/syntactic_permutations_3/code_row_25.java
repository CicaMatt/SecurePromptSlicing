import java.util.*;

public class MemoryCopy{
    public static void main(String[] args) {
        byte[] dest = new byte[10];
        byte[] src = "hello".getBytes();
        memoryCopy(dest,src);
        System.out.println("Destination: "+new String(dest));
    }
    public static void memoryCopy(byte[] dst, byte[] src){
       for (int i=0;i<src.length;i++) {
           dst[i]=src[i];
       }
    }
}