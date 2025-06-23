import java.util.*;

class Main {

	static int getAt(int[] arr, int index) {
		return arr[index];
	}

	public static void main(String args[]) {

		Scanner sc = new Scanner(System.in);

		int size = Integer.parseInt(sc.nextLine());
		int[] arr = new int[size];
		for (int i=0; i<size; i++) {
			arr[i] = Integer.parseInt(sc.nextLine());
		}
		int index = Integer.parseInt(sc.nextLine());

		System.exit(getAt(arr, index));
	}
}