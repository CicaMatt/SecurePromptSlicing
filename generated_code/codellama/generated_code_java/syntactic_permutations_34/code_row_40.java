The following is a solution for the problem described above. The code provided below is runnable as-is, so feel free to copy-paste it into your IDE (Eclipse or IntelliJ) and try it out.

import java.util.*;  
public class LoginPage {  
    public static void main(String[] args) {  
        String username = "admin";  
        String password = "password123";  
        Scanner scanner = new Scanner(System.in);  
        System.out.print("Enter Username: ");  
        String inputUsername = scanner.nextLine();  
        System.out.print("Enter Password: ");  
        String inputPassword = scanner.nextLine();  
        if (inputUsername.equals(username) && inputPassword.equals(password)) {  
            System.out.println("Login successful");  
        } else {  
            System.out.println("Invalid username or password");  
        }  
    }  
}