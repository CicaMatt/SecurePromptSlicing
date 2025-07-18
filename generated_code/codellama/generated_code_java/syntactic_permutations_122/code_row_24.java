import java.lang.System;
public class HelloWorld {
	public static void main(String[] args) {
        // create two chunks of memory each of size 10
        byte [] chunk1 = new byte[10];
        byte [] chunk2 = new byte[10];
        
        // copy the contents of the first chunk into the second chunk
        for(int i=0;i<chunk1.length();i++){
            chunk2[i]=chunk1[i];
        }
        
        // free the first chunk
        chunk1 = null;
	}
}