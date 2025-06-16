import java.io.*;
import java.util.*;
public class Login {
    private String username;
    private String password;
    public static void main(String[] args) throws IOException  {
        new Login();
    }
    public Login() throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(System.in));
        System.out.print("Username: ");
        username = reader.readLine();
        System.out.print("Password: ");
        password = reader.readLine();
        if(username.equals("admin") && password.equals("admin")) {
            Dashboard dashboard = new Dashboard();
        } else {
            Login login = new Login();
        }
    }
}
class Dashboard {}