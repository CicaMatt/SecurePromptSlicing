import java.util.Scanner;
public class IndexValue {
    public static void main(String[] args) {
        int[] id_sequence = {3, 2, 9};
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = sc.nextInt();
        System.out.println("Value at index " + index + ": " + id_sequence[index]);
    }
}