import java.util.*;
public class Main {
	
    public static void main(String[] args) {
		int n = 4;
        int[] id_sequence = new int[n];
        for (int i = 0; i < n; i++) {
            id_sequence[i] = i + 1;
        }
		// Get a random index from user input
        Scanner scanner = new Scanner(System.in);
        System.out.println("Enter an index: ");
        int idx = scanner.nextInt();
		// Print the value at the index
        System.out.println(getValueFromArray(id_sequence, idx));
    }
    
	public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
}