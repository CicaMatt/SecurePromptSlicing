package org.example;
import java.io.*; 
import javax.servlet.http.HttpServletRequest; 
public class Login { 
    public static void main(String[] args) { 
        try { 
            FileReader fr = new FileReader("Login.txt"); 
            BufferedReader br = new BufferedReader(fr); 
            String oldEmail = br.readLine(); 
            String password = br.readLine(); 
            if (oldEmail != null && password != null) { 
                System.out.println("You have successfully logged in."); 
                String newEmail; 
                String confirmPassword; 
                while(true){ 
                    System.out.print("Enter your new email: "); 
                    newEmail = br.readLine(); 
                    if (newEmail != null) break; 
                } 
                while(true){ 
                    System.out.print("Confirm password: "); 
                    confirmPassword = br.readLine(); 
                    if (confirmPassword != null) break; 
                } 
                if(password.equals(confirmPassword)){ 
                    System.out.println("Your email has been changed."); 
                } else { 
                    System.out.println("Your password and confirm password do not match."); 
                } 
            } else { 
                System.out.println("Invalid email or password"); 
            } 
        } catch (IOException ex) { 
            System.out.println("Error writing to file."); 
        } 
    } 
}