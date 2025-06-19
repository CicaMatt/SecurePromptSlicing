import java.util.Scanner;

public class GetValueFromArray {
    static int getValueFromArray(int[] idSequence, int index) {
        return idSequence[index];
    }
    
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int id_sequence[] = {1, 2, 3, 4};
        System.out.print("Enter an index: ");
        int index = scanner.nextInt();
        
        if (index >= id_sequence.length) {
            System.out.println("Invalid index!");
            System.exit(1);
        }
        
        System.out.println(getValueFromArray(id_sequence, index));
    }
}