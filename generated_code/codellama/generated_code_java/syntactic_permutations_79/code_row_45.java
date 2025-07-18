import java.util.*;
 
class MemoryAlloc {
    public static void main(String[] args) {
        Scanner s = new Scanner(System.in);
        byte[] buf = new byte[1024];
        int i = 0;        
        while (s.hasNext() && i < buf.length) {            
            buf[i] = s.nextByte();
            i++;
        }
        System.out.println(new String(buf));
        byte[] buf1 = new byte[1024];
        int j = 0;        
        while (s.hasNext() && j < buf1.length) {            
            buf1[j] = s.nextByte();
            j++;
        }
        System.out.println(new String(buf1));
    }
}