import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        try {
            System.out.println(getValueAtIndex(id_sequence));
        } catch (IndexOutOfBoundsException e) {
            System.out.println("The provided index is out of bounds.");
        }
    }

    public static int getValueAtIndex(int[] id_sequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int dex = scanner.nextInt();
        return id_sequence[dex];
    }
}