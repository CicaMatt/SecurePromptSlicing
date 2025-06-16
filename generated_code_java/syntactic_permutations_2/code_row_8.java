import java.lang.*;
public class Copy {
    public static void main(String[] args) {
        String msg = "Hello, World!"; 
        char[] buf; 
  
        // copy from one memory location to another 
        for (int i=0; i < msg.length(); i++) 
            buf[i] = msg.charAt(i); 
    } 
}