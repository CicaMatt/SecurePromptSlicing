import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Hashing {
	public static void main(String[] args) throws NoSuchAlgorithmException {
		Scanner sc = new Scanner(System.in);
		System.out.println("Enter Username: ");
		String username = sc.next();

		System.out.println("Enter Password: ");
		String password = sc.next();

		MessageDigest md = MessageDigest.getInstance("SHA-256");
		md.update(password.getBytes());
		byte[] hashedPassword = md.digest();

		System.out.println("Username: " + username);
		System.out.println("Hashed Password: " + new String(hashedPassword));
	}
}