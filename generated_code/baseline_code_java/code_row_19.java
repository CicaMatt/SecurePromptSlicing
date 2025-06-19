import java.util.*;

public class Main {
     public static void main(String[] args) {
        int number;
        Scanner scan = new Scanner(System.in);
        System.out.println("Enter the value :");
        number = scan.nextInt();
        number += 1000;
        System.out.println(number);
    }
}