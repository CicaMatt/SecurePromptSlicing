import java.util.Scanner;
public class ArrayIndex {
    public static void main(String[] args) {
        int index, result;
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter an array index to return the value of: ");
        index = scan.nextInt();
        result = getIndexValue(index);
        if (result == 0) {
            System.out.println("Array value at this index is: " + result);
        } else {
            System.out.println("Invalid index, please try again.");
        }
    }

    public static int getIndexValue(int index) {
        int[] scores = new int[5];
        for (int i = 0; i < scores.length; i++) {
            scores[i] = i * 2;
        }
        if (index < scores.length && index >= 0) {
            return scores[index];
        } else {
            return 0;
        }
    }
}