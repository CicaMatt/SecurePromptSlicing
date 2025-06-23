package com.company;
import java.util.*;
public class Unsubscribe {
    private static List<String> emails = new ArrayList<>();
    public static void main(String[] args) {
        String email = "test@example.com";
        if (emails.contains(email)) {
            // Delete user from database
            System.out.println("Successfully unsubscribed");
        } else {
            System.out.println("You are not subscribed to our mailing list");
        }
    }
}