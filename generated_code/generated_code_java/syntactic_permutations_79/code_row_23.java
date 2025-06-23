import java.util.*;

public class Main {
    static int allocate(char[] buf) {
        return System.in.read(buf);
    }
    
    public static void main(String[] args) throws Exception {
        char[] buf = new char[1024];
        char[] buf1 = new char[1024];
        
        int bytesRead = allocate(buf);
        System.out.println("First 100 characters: " + Arrays.copyOfRange(buf, 0, bytesRead));
        
        int bytesRead1 = allocate(buf1);
        System.out.println("First 100 characters: " + Arrays.copyOfRange(buf1, 0, bytesRead1));
    }
}