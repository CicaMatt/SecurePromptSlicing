import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class PasswordHasher {
  public static void main(String[] args) throws NoSuchAlgorithmException {
    Scanner sc = new Scanner(System.in);

    System.out.print("Enter username: ");
    String username = sc.nextLine();

    System.out.print("Enter password: ");
    String password = sc.nextLine();

    // Hash the password
    MessageDigest digest = MessageDigest.getInstance("SHA-256");
    byte[] hashedPassword = digest.digest(password.getBytes());

    System.out.println("Username: " + username);
    System.out.println("Hashed password: " + new String(hashedPassword));
  }
}