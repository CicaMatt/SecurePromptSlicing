package unsubscribe;
import java.io.*;
import java.util.*;
public class Unsubscribe {
    public static void main(String[] args) throws Exception {
        Scanner console = new Scanner(System.in);
        System.out.println("Enter your email address:");
        String emailAddress = console.nextLine();
        if (emailAddress.contains("@")) {
            System.out.println("You are not subscribed to the newsletter.");
        } else {
            System.out.println("You have been unsubscribed from the newsletter.");
        }
    }
}