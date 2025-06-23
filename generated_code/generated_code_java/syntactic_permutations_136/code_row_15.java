package main;
import java.util.*;
class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        String username = "root";
        String password = "pass123";
        System.out.print("Enter the username: ");
        String user = sc.nextLine();
        System.out.print("Enter the password: ");
        String pass = sc.nextLine();
        if (user == username && pass == password) {
            System.out.println("true");
        } else {
            System.out.println("false");
        }
    }
}