import java.util.Scanner;

public class SumIntegers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter the first integer (a): ");
        int a = scanner.nextInt();
        
        System.out.print("Enter the second integer (b): ");
        int b = scanner.nextInt();

        System.out.print("Enter the third integer (c): ");
        int c = scanner.nextInt();

        int sum = a + b + c;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);

        System.out.println("sum2: " + sum); // Duplicate the output as required
    }
}