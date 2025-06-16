import java.util.*;

class Main {
public static void main(String[] args) {
        int[] idSequence = {12345, 67890};
		System.out.print("Enter an index (0 or 1): ");
		Scanner input = new Scanner(System.in);
		int index = Integer.parseInt(input.nextLine());
        System.out.println(idSequence[index]);
    }
}