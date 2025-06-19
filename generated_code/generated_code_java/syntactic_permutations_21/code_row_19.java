import java.util.*;
public class AddOneThousand {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Input a value to be added 1000: ");
        int num = sc.nextInt();
        System.out.println("The result of adding 1000 is " + (num+1000));
    }
}