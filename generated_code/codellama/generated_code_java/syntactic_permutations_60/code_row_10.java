import java.io.*;
class Main {
	public static void main(String[] args) throws Exception {
		int n = Integer.parseInt(args[0]);
		byte[] b = new byte[n];
		for (int i = 0; i < n; i++) {
			b[i] = (byte)(i%127+1);
		}
		System.out.println(new String(b));
	}
}