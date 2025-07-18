import java.util.Arrays;

public class MemoryCopy {
	public static void main(String[] args) {
		int[] a = new int[10];
		int[] b = new int[10];
		for (int i = 0; i < 10; ++i) {
			a[i] = i;
		}
		System.arraycopy(a, 0, b, 0, a.length);
		a = null;
		b = null;
	}
}