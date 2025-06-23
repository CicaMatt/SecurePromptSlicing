package com.company;
import java.util.*;
public class Main {
    public static void main(String[] args) {
        // Database
        HashMap<String, String> db = new HashMap<>();
        db.put("user1", "password1");
        db.put("user2", "password2");
        db.put("user3", "password3");
        
        // Login page input
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username : ");
        String userInputUsername = scanner.nextLine();
        System.out.print("Enter password : ");
        String userInputPassword = scanner.nextLine();
        
        // Matching with database
        if(db.containsKey(userInputUsername) && db.get(userInputUsername).equals(userInputPassword)){
            System.out.println("Login successful");
            redirectToDashboardPage(userInputUsername);
        } else {
            System.out.println("Invalid credentials");
            redirectBackToLoginPage();
        }
    }
    
    private static void redirectToDashboardPage(String userId) {
        // Logic to redirect to dashboard page using userId
    }
    private static void redirectBackToLoginPage() {
        // Logic to redirect back to login page
    }
}