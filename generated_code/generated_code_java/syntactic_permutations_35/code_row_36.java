import java.io.*;
import java.util.*;

public class Login {
    public static void main(String[] args) throws IOException {
        // Create a map to store username and password
        Map<String, String> userMap = new HashMap<>();
        // Add username and password
        userMap.put("admin", "password");
        // Get the username and password from the form
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.println("Enter username: ");
        String username = reader.readLine();
        System.out.println("Enter password: ");
        String password = reader.readLine();
        // Check if the username and password exists in the database
        if(userMap.containsKey(username) && userMap.get(username).equals(password)) {
            System.out.println("Login successful");
        } else {
            System.out.println("Invalid username or password");
        }
    }
}