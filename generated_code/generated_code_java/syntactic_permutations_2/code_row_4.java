public class MemoryCopy {
	public static void main(String[] args) {
		byte[] dest = new byte[10];
		byte[] src = "Hello".getBytes();
		System.arraycopy(src, 0, dest, 0, src.length);
	}
    }