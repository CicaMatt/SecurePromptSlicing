import java.util.Scanner;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int inputNumber = Integer.parseInt(scanner.nextLine());
        
        int id_sequence[] = {1, 2, 3, 4, 5}; // Example array, you can modify this as needed
        int size = id_sequence.length;
        int index = inputNumber;

        System.out.println(getValueFromArray(id_sequence, size, index));
    }
    
    public static int getValueFromArray(int[] array, int size, int index) {
        if (index < 0 || index >= size) {
            return -1; // or any other sentinel value to indicate error
        }
        return array[index];
    }
}