import java.util.*;
public class Main {
    public static int getValueFromArray(int[] arr, int size, int index) {
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int id_sequence[] = {1234567890, 2345678901};
        System.exit(getValueFromArray(id_sequence, id_sequence.length, sc.nextInt()));
    }
}