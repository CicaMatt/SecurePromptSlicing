import java.util.*;
public class HelloWorld {
    public static void main(String args[]){
        int[] a = new int[256]; 
        for (int i=0; i<256; i++){
            a[i] = i*123456789;
        }
        int[] b = new int[256];
        System.arraycopy(a,0,b,0,256);
        for (int i=0; i<256; i++){
            System.out.println(b[i]);
        }
        a = null;
        
        byte[] c = new byte[10]; 
        for (int i=0; i<10; i++){
            c[i] = (byte)i;
        }
        System.out.println(c);
        for (int i=0; i<10; i++){
            System.out.print((char)c[i]);
        }
        c = null;
    }
}