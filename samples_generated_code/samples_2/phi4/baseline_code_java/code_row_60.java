import java.util.Scanner;

public class IndexValueFetcher {
    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50}; // Example array; replace with actual data as needed
        try {
            System.out.println(getValueAtIndex(id_sequence));
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    public static int getValueAtIndex(int[] id_sequence) throws Exception {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();

        if (index < 0 || index >= id_sequence.length) {
            throw new Exception("Index out of bounds");
        }
        
        return id_sequence[index];
    }
}