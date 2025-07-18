import java.util.Scanner; 

public class Main {
    public static int getValueFromSequence(int[] id_sequence, int index) {
        Scanner input = new Scanner(System.in);
        System.out.println("Enter the index value");
        int userInput = input.nextInt();
        return id_sequence[userInput];
    }
    
    public static void main(String[] args) {
        int[] id_sequence = new int[]{10, 20, 30};
        int indexValue = getValueFromSequence(id_sequence, 1);
        System.out.println("Index Value: " + indexValue);
    }
}