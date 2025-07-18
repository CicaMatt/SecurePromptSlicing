import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;

public class EmptyBuffer {
	public static void main(String[] args) throws IOException {
		File file = new File("path/to/file");
		byte[] buffer = new byte[1024];
		int bytesRead;
		try (FileInputStream in = new FileInputStream(file)) {
			bytesRead = in.read(buffer);
		}
		if (bytesRead == 0) {
			System.out.println("Buffer is empty");
		} else {
			try (FileOutputStream out = new FileOutputStream("path/to/file")) {
				for (int i = 0; i < bytesRead; ++i) {
					out.write(buffer[i]);
				}
			}
		}
	}
}