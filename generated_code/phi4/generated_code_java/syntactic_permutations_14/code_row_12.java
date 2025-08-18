import java.util.Scanner;

public class ArrayIndexAccessor {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(id_sequence));
    }

    public static Integer getValueAtIndex(int[] idSequence) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < idSequence.length) {
            return idSequence[index];
        } else {
            System.out.println("Index out of bounds.");
            return null;
        }
    }
}