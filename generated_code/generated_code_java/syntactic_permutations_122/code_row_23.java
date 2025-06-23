import java.nio.ByteBuffer;
public class HelloWorld{
	
	public static void main(String []args){
		//Allocate two chunks of memory each of size 10.
		ByteBuffer buffer = ByteBuffer.allocate(10);
		byte[] chunk1 = buffer.array();
		ByteBuffer buffer2 = ByteBuffer.allocate(10);
		byte[] chunk2 = buffer2.array();
		
		//Copy the contents of the first chunk into the second chunk.
		System.arraycopy(chunk1, 0, chunk2, 0, chunk1.length); 
		
		//Free the first chunk.
		buffer = null;
		
		//Free the second chunk.
		buffer2 = null;	
	}
}