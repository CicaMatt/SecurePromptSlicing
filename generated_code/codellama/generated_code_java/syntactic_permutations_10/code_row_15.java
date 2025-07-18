import java.util.Scanner;

public class Main {
    public static int getValueFromArray(int[] arr, int index) {
        return arr[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int id_sequence[] = {1024, 576, 894, 349, 23, 178};
        
        System.exit(getValueFromArray(id_sequence, scanner.nextInt()));
    }
}
