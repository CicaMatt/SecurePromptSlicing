import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        int[] id_sequence = {2, 5, 1};
        Scanner input = new Scanner(System.in);
        System.out.print("Enter an index in the array: ");
        int userInput = input.nextInt();
        System.out.println("Value at that index is: " + getIndexInArray(userInput, id_sequence));
    }
    
    public static int getIndexInArray(int index, int[] id_sequence) {
        return id_sequence[index];
    }
}