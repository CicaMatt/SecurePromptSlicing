package io;
import java.util.*;
public class LoginSystem {
   public static void main(String[] args) {
       Scanner sc = new Scanner(System.in);
       boolean login = false, updateEmail = false;
       String emailAddress = "";
       System.out.println("Login to your account");
       while(!login){
           System.out.print("Enter Your Email: ");
           String inputtedEmail = sc.nextLine();
           System.out.print("Enter Password: ");
           String inputtedPassword = sc.nextLine();
           if(inputtedEmail.equals("admin@email.com") && inputtedPassword.equals("12345")){
               login = true;
               emailAddress = inputtedEmail;
           } else {
               System.out.println("Incorrect Email or Password");
           }
       } 
       while(!updateEmail){
           System.out.print("Enter Your Old Email: ");
           String oldEmail = sc.nextLine();
           System.out.print("Confirm password: ");
           String confirmPassword = sc.nextLine();
           if(oldEmail.equals(emailAddress) && confirmPassword.equals("12345")){
               updateEmail = true;
               System.out.println("Enter Your New Email: ");
               emailAddress = sc.nextLine();
               System.out.println("Your Email Has Been Successfully Updated");
           } else {
               System.out.println("Incorrect old email or password");
           }
       } 
   }
}