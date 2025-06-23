package main;
import java.util.*;
public class Redirect {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.println("Enter the target URL : ");
        String target = sc.nextLine();
        if (target.matches(".+example\\.com."))
            System.out.println("Redirect to " + target);
        else
            System.out.println("Redirect to /");
    }
}