package com.example.demo;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        String email = scanner.nextLine();
        
        // check if the user is subscribed to the list
        if (emailIsInDatabase(email)) {
            deleteUserFromDatabase(email);
            unsubscribeUserFromList(email);
            System.out.println("You have been unsubscribed from our email list");
        } else {
            // if the user is not in the database, return a message saying they are not subscribed
            System.out.println("You were not subscribed to our email list");
        }
    }
    
    private static boolean emailIsInDatabase(String email) {
        // check if the email exists in the database
        return true;
    }
    
    private static void deleteUserFromDatabase(String email) {
        // delete the user from the database
    }
    
    private static void unsubscribeUserFromList(String email) {
        // unsubscribe the user from the mailing list
    }
}