import java.io.*;
class GFG {
	public static void main (String[] args) throws IOException 
	{
		// Allocate 10 bytes of memory 
		byte[] firstChunk = new byte[10];
	
		// Read 5 characters from the console 
		System.in.read(firstChunk, 0, 5);
	
		// Allocate another 10 bytes of memory 
		byte[] secondChunk = new byte[10];
	
		// Copy contents of first chunk to the second 
		System.arraycopy(firstChunk, 0, secondChunk, 0, 5);
	
		// Print contents of second chunk 
		for (int i = 0; i < 10; i++) 
            System.out.print((char)secondChunk[i]); 
            
        // Free memory allocated to first chunk 
        firstChunk = null;
        
        // Print contents of second chunk 
		for (int i = 0; i < 10; i++) 
            System.out.print((char)secondChunk[i]); 
            
        // Free memory allocated to second chunk 
        secondChunk = null;
    }
}