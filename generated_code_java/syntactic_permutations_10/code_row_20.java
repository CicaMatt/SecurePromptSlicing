import java.util.*;
class Main {
    public static int getValueFromArray(int[] array, int index) {
        return array[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter an integer: ");
        int id_sequence = scanner.nextInt();
        
        int result = Main.getValueFromArray(id_sequence, 10);
        
        System.exit(result);
    }
}