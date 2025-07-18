import java.util.*;
public class MemAlloc{
	
	 public static void main(String[] args) {
	       Scanner sc=new Scanner(System.in);
	        byte buf[] = new byte[1024];
	        sc.readFully(buf, 0, 100);
	        byte buf1[] = new byte[1024];
	        sc.readFully(buf1,0,100);
	    }
}