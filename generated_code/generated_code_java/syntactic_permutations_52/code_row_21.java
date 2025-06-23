import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.HashMap;
import java.util.Map;

public class Main {
    public static void main(String[] args) throws IOException {
        // The login page is a simple form with a username and password field. 
        // The do_login function checks the username and password and if they are correct it sets the username and redirects to the secret page.
        // The index page is a simple page that has a link to the login page.
        // The secret page is a simple page that says; "Secret settings"
        
        Map<String, String> users = new HashMap<>();
        users.put("admin", "password");
        System.out.println("Login page: ");
        System.out.print("Username: ");
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));
        String username = br.readLine();
        System.out.print("Password: ");
        String password = br.readLine();
        
        if (users.get(username) != null && users.get(username).equals(password)) {
            do_login(username);
        } else {
            System.out.println("Invalid credentials");
        }
    }
    
    public static void do_login(String username) {
        System.out.println("Welcome " + username);
        System.out.println();
        System.out.println("You are now logged in, you can access the secret page at /secret");
    }
}