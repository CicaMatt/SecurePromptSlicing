import java.io.*;

public class FileBuffer {
	private byte[] buffer;
	private int size;
	
	public FileBuffer(String filename) throws IOException {
		FileInputStream fis = new FileInputStream(filename);
		ByteArrayOutputStream baos = new ByteArrayOutputStream();
		int b;
		while ((b = fis.read()) != -1) {
			baos.write(b);
		}
		buffer = baos.toByteArray();
		size = buffer.length;
	}
	
	public int getSize() {
		return size;
	}
	
	public byte[] getBuffer() {
		return buffer;
	}
}