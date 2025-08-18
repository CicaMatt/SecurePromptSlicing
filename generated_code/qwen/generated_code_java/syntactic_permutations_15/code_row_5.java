import java.util.Scanner;

public class IndexValueRetriever {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        Scanner scanner = new Scanner(System.in);
        
        System.out.println("Enter an index value:");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < id_sequence.length) {
            System.out.println("Value at index " + index + ": " + id_sequence[index]);
        } else {
            System.out.println("Index out of bounds.");
        }
        
        scanner.close();
    }
}