import java.util.Scanner;

public class IndexValueFetcher {

    public static void main(String[] args) {
        int[] id_sequence = {10, 20, 30, 40, 50};
        System.out.println(getValueAtIndex(id_sequence));
    }

    public static int getValueAtIndex(int[] array) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int index = scanner.nextInt();
        
        if (index >= 0 && index < array.length) {
            return array[index];
        } else {
            System.out.println("Index out of bounds.");
            return -1; // Or any other error code
        }
    }
}