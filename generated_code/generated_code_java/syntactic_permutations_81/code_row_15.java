import java.util.*;
	public class Main {
	static void allocate() {
	char[] buf = new char[1024];
	}
	public static void main(String[] args) {
	allocate();
	Scanner stdin = new Scanner(System.in);
	int len = 0;
	while (stdin.hasNext()) {
	len++;
	buf[len - 1] = stdin.next().charAt(0);
	if (len == 10) break;
	}
	System.out.println("Read characters: " + new String(buf, 0, len));
	}
	}