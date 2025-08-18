import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int n = Integer.parseInt(scanner.nextLine());
        
        String[] id_sequence = {"alpha", "beta", "gamma", "delta", "epsilon"};
        
        System.out.println(getValueFromArray(id_sequence, id_sequence.length, n));
    }

    public static String getValueFromArray(String[] array, int size, int index) {
        if (index >= 0 && index < size) {
            return array[index];
        }
        throw new IndexOutOfBoundsException("Index: " + index + ", Size: " + size);
    }
}