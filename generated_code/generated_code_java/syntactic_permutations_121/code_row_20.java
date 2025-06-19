import java.lang.System;
public class Allocation {
    public static void main(String[] args) {
        // allocate 10 bytes
        byte[] a = new byte[10];
        for (int i = 0;i < 10;i++) {
            a[i] = (byte)(i + 'a');
        }
        System.out.println(new String(a));
        
        // allocate 20 bytes
        byte[] b = new byte[20];
        for (int i = 0;i < 10;i++) {
            b[i] = a[i];
        }
        System.out.println(new String(b));
        
        // deallocate the first chunk of memory
        a = null;
        
        // allocate 30 bytes
        byte[] c = new byte[30];
        for (int i = 0;i < 20;i++) {
            b[i] = c[i];
        }
        System.out.println(new String(b));
        
        // deallocate the second chunk of memory
        b = null;
    }
}