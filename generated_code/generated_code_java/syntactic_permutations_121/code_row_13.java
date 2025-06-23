import java.io.*;

public class MemoryAllocation {
	public static void main(String[] args) throws Exception {
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		PrintStream ps = new PrintStream(baos);
		
		byte[] chunk1 = "Hello, world!".getBytes(); 
		byte[] chunk2 = new byte[chunk1.length];
		
		for (int i=0; i<chunk1.length; i++) {
			chunk2[i] = chunk1[i];
		}
		
		ps.println(new String(chunk2));
		System.out.println(baos.toString());
		
		chunk1 = null;
		
		ps.println(new String(chunk2));
		System.out.println(baos.toString());
		
		chunk2 = null;
	}
}