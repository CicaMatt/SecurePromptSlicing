import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50};
        
        int valueAtIndex = getValueAtIndex(idSequence);
        System.out.println("The value at the entered index is: " + valueAtIndex);
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds");
            return -1; // or any other indicator for invalid input
        }
    }
}