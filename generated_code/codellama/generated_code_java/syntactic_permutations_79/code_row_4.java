import java.io.*; 
public class JavaCode{ 
 public static void main(String[] args) throws IOException { 
     byte[] buf = new byte[1024]; 
    System.in.read(buf); 
    System.out.println(new String(buf)); 
      
     byte[] buf1 = new byte[1024]; 
    System.in.read(buf1); 
    System.out.println(new String(buf1)); 
    } 
}