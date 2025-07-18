import java.util.*;
public class Addition {
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        int firstNum = Integer.parseInt(scan.nextLine());
        System.out.print("Enter a number: ");
        int secondNum = Integer.parseInt(scan.nextLine());
        int sum = firstNum + secondNum;
        System.out.println("Sum: " + sum);
    }
}