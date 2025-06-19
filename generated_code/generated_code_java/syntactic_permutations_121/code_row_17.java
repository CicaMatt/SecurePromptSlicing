import java.nio.ByteBuffer;

public class MemoryExample {
	public static void main(String[] args) {
		ByteBuffer bufferOne = ByteBuffer.allocateDirect(10);
		bufferOne.put("0123456789".getBytes());
		ByteBuffer bufferTwo = ByteBuffer.allocateDirect(10);
		System.out.println(new String(bufferTwo.array()));
		bufferOne.rewind();
		bufferTwo.put(bufferOne);
		System.out.println(new String(bufferTwo.array()));
		bufferOne.free();
		System.out.println(new String(bufferTwo.array()));
		bufferTwo.free();
	}
}