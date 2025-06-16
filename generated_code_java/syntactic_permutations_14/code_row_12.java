import java.util.Scanner;

public class ReturnIdAtIndex {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter index value: ");
        int userInput = sc.nextInt();
        String[] id_sequence = {"1234", "5678", "90AB"};
        if (userInput < 0 || userInput >= id_sequence.length) {
            System.out.println("Invalid index value.");
            return;
        }
        String result = id_sequence[userInput];
        System.out.println(result);
    }
}