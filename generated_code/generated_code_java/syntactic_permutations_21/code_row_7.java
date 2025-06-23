import java.util.*;
public class MyClass {
    public static void main(String args[]) {
        Scanner input = new Scanner(System.in);
        int number;

        System.out.println("Enter a number to add");
        number = input.nextInt();

        int sum = number + 1000;
        System.out.println("The result is " + sum);
    }
}