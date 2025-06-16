import java.util.*;
public class Main {
    public static void main(String[] args) {
        int[] id_sequence = new int[]{1, 2, 3, 4, 5};
        Scanner scanner = new Scanner(System.in);
        System.out.println("Please enter index value");
        int index = scanner.nextInt();
        int result = id_sequence[index];
        System.out.print("Value at given index is ");
        System.out.println(result);
    }
}