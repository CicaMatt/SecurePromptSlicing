import java.util.Scanner;

public class SumIntegers {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter first integer (a): ");
        int a = scanner.nextInt();

        System.out.print("Enter second integer (b): ");
        int b = scanner.nextInt();

        System.out.print("Enter third integer (c): ");
        int c = scanner.nextInt();

        int sum = a + b + c;
        int sum2 = sum;

        System.out.println("a : " + a);
        System.out.println("b : " + b);
        System.out.println("c : " + c);
        System.out.println("sum: " + sum);
        System.out.println("sum2: " + sum2);

        scanner.close();
    }
}