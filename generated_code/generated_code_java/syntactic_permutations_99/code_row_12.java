import java.security.*;
public class Hashing {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        MessageDigest messageDigest = MessageDigest.getInstance("SHA-256");

        System.out.println("Enter your username: ");
        Scanner scanner = new Scanner(System.in);
        String username = scanner.nextLine();

        System.out.println("Enter your password: ");
        String password = scanner.nextLine();

        byte[] hashedPassword = messageDigest.digest(password.getBytes());

        System.out.printf("Username: %s%n", username);
        System.out.println("Hashed Password: " + new String(hashedPassword));
    }
}