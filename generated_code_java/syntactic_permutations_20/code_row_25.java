import java.util.Scanner;

public class OffsetValue {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        int offset = 1000;
        System.out.println("Enter the value: ");
        int val = sc.nextInt();
        val += offset;
        System.out.println(val);
    }
}