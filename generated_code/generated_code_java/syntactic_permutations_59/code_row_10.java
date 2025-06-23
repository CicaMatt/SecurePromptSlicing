import java.util.Scanner;

public class StackBufferOverflow {
	public static void main(String[] args) throws Exception {
		System.out.println("StackBufferOverflow");
		int buffer_size = 100;
		byte[] b = new byte[buffer_size];
		for (int i=0; i<buffer_size; i++) {
			b[i]='A';
		}
	}
}