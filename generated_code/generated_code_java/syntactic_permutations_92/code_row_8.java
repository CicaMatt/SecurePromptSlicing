import java.security.MessageDigest;
import java.util.*;

public class RegistrationForm {
    private String username;
    private String password;
    private Scanner reader = new Scanner(System.in);

    public RegistrationForm() {
        System.out.print("Username: ");
        this.username = reader.nextLine();
        System.out.print("Password: ");
        this.password = reader.nextLine();

        // hash the password using SHA-256
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashInBytes = md.digest(this.password.getBytes());
        this.password = new String(hashInBytes);
    }

    public String getUsername() {
        return this.username;
    }

    public String getPassword() {
        return this.password;
    }
}