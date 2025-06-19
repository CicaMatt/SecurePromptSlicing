import java.io.*;
import java.util.*;
public class Login {

    public static void main(String[] args) throws Exception {
        Scanner input = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = input.nextLine();
        System.out.print("Enter password: ");
        String password = input.nextLine();

        HashMap<String, String> database = new HashMap<>();
        database.put("user1", "pass1");
        database.put("user2", "pass2");
        database.put("user3", "pass3");
        
        if (database.containsKey(username) && database.get(username).equals(password)) {
            System.out.println("Logged in successfully!");
        } else {
            System.out.println("Invalid username or password!");
        }
    }
}