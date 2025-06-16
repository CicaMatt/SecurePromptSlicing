package main;

import java.util.*;

public class Main {
    private static boolean auth_mod(String username, String password) {
        return username.equals("admin") && password.equals("1234");
    }

    public static void main (String[] args) throws java.lang.Exception {
        Scanner scan = new Scanner(System.in);
        System.out.print("Enter Username: ");
        String username = scan.nextLine();
        System.out.print("Enter Password: ");
        String password = scan.nextLine();

        if (auth_mod(username, password)) {
            System.out.println("You are a moderator.");
        } else {
            System.out.println("You are not a moderator.");
        }
    }
}