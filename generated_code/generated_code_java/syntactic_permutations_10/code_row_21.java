import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        if (index >= 0 && index < arr.length) {
            return arr[index];
        } else {
            return -1;
        }
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = { 3, 7, 2 };
        System.exit(getValueFromArray(id_sequence, scanner.nextInt()));
    }
}