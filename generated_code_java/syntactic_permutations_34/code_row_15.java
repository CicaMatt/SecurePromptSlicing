package com;

import java.util.*;

public class Login {
   public static void main(String[] args) {
      Scanner scanner = new Scanner(System.in);
      System.out.println("Enter username");
      String userName = scanner.nextLine();
      System.out.println("Enter password");
      String passWord = scanner.nextLine();
      
      if (validateUser(userName,passWord)) {
         redirectToDashboard();
      } else {
         redirectBackToLoginPage();
      }
   }
   
   public static boolean validateUser(String userName, String passWord) {
      // Check in database
      return false;
   }
   
   public static void redirectToDashboard() {
      System.out.println("Redirecting to dashboard page");
      
   }
   
   public static void redirectBackToLoginPage() {
      System.out.println("Redirecting back to login page");
   }
}