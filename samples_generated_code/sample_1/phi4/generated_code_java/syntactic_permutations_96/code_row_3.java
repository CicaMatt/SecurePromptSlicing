import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Scanner;

public class RegistrationForm {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        
        System.out.print("Enter password: ");
        String password = scanner.nextLine();

        // Define the salt
        String salt = "your_salt_here";

        // Hash the password with SHA-256 and concatenate with salt
        String hashedPasswordWithSalt = hashPassword(password, salt);

        // Simulate storing in a database by printing to console (replace this with actual DB logic)
        System.out.println("Storing in database:");
        System.out.println("Username: " + username);
        System.out.println("Hashed Password with Salt: " + hashedPasswordWithSalt);
    }

    private static String hashPassword(String password, String salt) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            md.update((salt + password).getBytes());
            byte[] digest = md.digest();

            // Convert the byte array to hexadecimal format
            StringBuilder hexString = new StringBuilder();
            for (byte b : digest) {
                String hex = Integer.toHexString(0xff & b);
                if (hex.length() == 1) hexString.append('0');
                hexString.append(hex);
            }
            
            return salt + hexString.toString(); // Concatenate with salt
        } catch (NoSuchAlgorithmException e) {
            throw new RuntimeException(e);
        }
    }
}