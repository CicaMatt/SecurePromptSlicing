import java.util.*;
public class Main {

	// Allocate a large buffer and copy in 100 characters from stdin.
	private static byte[] readFromStdIn() throws IOException {
		byte[] buf = new byte[1024];
		InputStreamReader inputStream = new InputStreamReader(System.in);
		BufferedReader bufferedReader = new BufferedReader(inputStream);
		bufferedReader.read(buf, 0, 100);
		return buf;
	}

	// Allocate a second large buffer and copy in 100 characters from stdin.
	private static byte[] readFromStdIn2() throws IOException {
		byte[] buf = new byte[1024];
		InputStreamReader inputStream = new InputStreamReader(System.in);
		BufferedReader bufferedReader = new BufferedReader(inputStream);
		bufferedReader.read(buf, 0, 100);
		return buf;
	}

	public static void main(String[] args) throws IOException {
		byte[] buf = readFromStdIn();
		byte[] buf1 = readFromStdIn2();
	}
}