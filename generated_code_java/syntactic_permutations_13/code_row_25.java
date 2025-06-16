import java.util.Scanner;
public class ArrayRetrieve {
    public static String[] id_sequence = {"435-213-7890", "642-325-9876"};
    
    public static void main(String[] args) {
        int userIndex;
        
        Scanner reader = new Scanner(System.in);  // Reading from System.in
        System.out.println("Enter an index value: ");
        userIndex = reader.nextInt(); // Scans the next token of the input as an int.

        retrieveValue(userIndex);
    }
    
    public static String retrieveValue(int index) {
        return id_sequence[index];
    }
}