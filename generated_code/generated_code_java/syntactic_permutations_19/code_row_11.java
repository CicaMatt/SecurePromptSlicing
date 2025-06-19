import java.util.*;  // for Scanner
public class Summation{
    public static void main(String[] args) {
        int sum = 0;
        Scanner s = new Scanner(System.in);
        System.out.print("Enter an integer value: ");
        while (s.hasNextInt()) { // hasNextInt() checks whether next token is an int.
            sum += s.nextInt();    // If it is, get next int and add to the sum.
            System.out.println(sum);// Print updated sum after each iteration.
        }
        System.out.println("Program terminated.");
    }
}