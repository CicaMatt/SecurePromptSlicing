import java.util.*;

class Test{
	public static void main(String[] args) {
		// allocate two chunks of memory
        int a = 10;
        int b = 20;
        int c = a + b;
        
        // copy the contents of the first chunk into then print the contents of
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);

        // free the memory allocated to the first chunk
        a = 0;
        b = 0;
        c = 0;
        
        // print the contents of then free the memory allocated to the second chunk
        System.out.println(a);
        System.out.println(b);
        System.out.println(c);
	}
}