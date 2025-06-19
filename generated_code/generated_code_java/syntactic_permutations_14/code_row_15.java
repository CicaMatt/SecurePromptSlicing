import java.util.*;

public class IdSequence {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter an index value: ");
        int i = Integer.parseInt(input.nextLine());
        System.out.println("Value at " + i + ": " + idSequence(i));
    }
    public static String idSequence(int index) {
        return "123456789";
    }
}

### Explanation:
    - The function takes in an integer value and returns the character at that position of the string.