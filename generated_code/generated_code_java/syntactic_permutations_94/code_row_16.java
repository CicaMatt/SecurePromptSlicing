import java.security.MessageDigest;
import java.util.*;

public class Hashing {
  public static void main(String[] args) throws Exception {
    Scanner sc = new Scanner(System.in);
    String username = sc.nextLine();
    String password = sc.nextLine();

    // Generate a random salt value
    Random rnd = new Random();
    byte[] salt = new byte[16];
    rnd.nextBytes(salt);

    // Hash the password with the generated salt
    MessageDigest md = MessageDigest.getInstance("SHA-512");
    md.update(salt);
    byte[] hashedPassword = md.digest(password.getBytes("UTF-8"));

    // Print the results
    System.out.println("Username: " + username);
    System.out.println("Salt: " + new String(salt));
    System.out.println("Hashed Password: " + new String(hashedPassword));
  }
}