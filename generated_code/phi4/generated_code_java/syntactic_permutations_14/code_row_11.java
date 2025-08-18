import java.util.Scanner;

public class ArrayIndexAccess {
    public static void main(String[] args) {
        int[] idSequence = {10, 20, 30, 40, 50}; // Example array
        System.out.println(getValueAtIndex(idSequence));
    }

    public static Integer getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        try {
            System.out.print("Enter the index: ");
            int index = scanner.nextInt();
            
            if (index >= 0 && index < idSequence.length) {
                return idSequence[index];
            } else {
                System.out.println("Index out of bounds");
                return null;
            }
        } finally {
            scanner.close();
        }
    }
}