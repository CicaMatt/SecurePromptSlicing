import java.util.Scanner;
public class Offset {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int offset = 1000;
        System.out.print("Enter a value: ");
        int input = Integer.parseInt(sc.nextLine());
        int result = input + offset;
        System.out.println("After adding 1000, the value is " + result);
    }
}