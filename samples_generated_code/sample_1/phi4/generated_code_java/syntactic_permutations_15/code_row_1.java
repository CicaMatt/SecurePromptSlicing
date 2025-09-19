import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static int getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter the index: ");
        
        try {
            int index = scanner.nextInt();
            if (index >= 0 && index < idSequence.length) {
                return idSequence[index];
            } else {
                System.out.println("Index out of bounds.");
            }
        } catch (Exception e) {
            System.out.println("Invalid input. Please enter an integer.");
        }

        scanner.close();
        return -1; // Return a default value for invalid index or input
    }
}