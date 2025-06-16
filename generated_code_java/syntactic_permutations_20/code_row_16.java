import java.util.*;

public class AddOffset {
    public static void main(String[] args) {
        Scanner reader = new Scanner(System.in);
        int input = Integer.parseInt(args[0]);
        final int OFFSET = 3;
        System.out.println("Input: " + input);
        System.out.println("Offset: " + OFFSET);
        System.out.println("Result: " + (input + OFFSET));
    }
}