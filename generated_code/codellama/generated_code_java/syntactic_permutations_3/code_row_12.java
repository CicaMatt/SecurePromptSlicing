import java.util.*;

    public class HelloWorld {
    	public static void main(String[] args) {
    		byte[] dest = new byte[6];
    		byte[] src = {72, 101, 108, 108, 111};
    		System.arraycopy(src, 0, dest, 0, 5);
    	}
    }