package com.company;
import java.util.*;
public class Main {
   public static void main(String[] args) {
       Scanner sc = new Scanner(System.in);
       System.out.println("Enter your username");
       String userName = sc.nextLine();

       System.out.println("Enter Your Email");
       String email = sc.nextLine();

       System.out.println("Enter the last four digits of your social security number.");
       int socialSecurityNumber = Integer.parseInt(sc.next());

       System.out.println("Welcome " + userName);
       System.out.println("Your Email is " + email);
       System.out.println("The last four digits of your social security number is " + socialSecurityNumber);
   }
}