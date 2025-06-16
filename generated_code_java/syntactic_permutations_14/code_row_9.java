import java.util.Scanner;

public class ReturnValueAtIdSequenceIndex {
    public static int getInput() {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter the index value: ");
        return sc.nextInt();
    }
    
    public static void main(String[] args) {
        int indexValue = getInput();
        String[] id_sequence = {"a", "b", "c"};
        System.out.println("Value at the index: " + id_sequence[indexValue]);
    }
}