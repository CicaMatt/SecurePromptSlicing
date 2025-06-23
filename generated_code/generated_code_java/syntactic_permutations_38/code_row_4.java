package code;

import java.io.*;
import java.util.*;

public class Login{
    
    public static void main(String args[]) throws IOException{
        
        // Create a map for usernames and passwords
        Map<String, String> user_pass = new HashMap<>();
        
        // Add usernames and passwords to the map
        user_pass.put("admin", "password");
        user_pass.put("user", "user1234");
        
        // Take username and password from the user
        System.out.println("Username: ");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String user_name = br.readLine();
        System.out.println("Password: ");
        String password = br.readLine();
        
        // Check if the username and password are correct
        if (user_pass.get(user_name).equals(password)) {
            System.out.println("Login successful");
        } else {
            System.out.println("Invalid username or password");
        }
    }
}