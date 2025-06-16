import java.nio.*;
class Main {
	public static void main(String[] args) {
		ByteBuffer buffer = ByteBuffer.allocate(10);
		buffer.putInt(12345678);
		buffer.putDouble(1.23);
		byte[] dest = new byte[10];
		buffer.flip();
		buffer.get(dest);
		System.out.println(buffer);
	}
}