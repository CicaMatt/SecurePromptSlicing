import java.security.*;
import javax.crypto.*;
import org.apache.commons.codec.digest.*;

public class Hash{
    public static void main(String[] args) {
        System.out.println("Enter username and password: ");
        Scanner sc = new Scanner(System.in);
        String userName = sc.nextLine();
        String passWord = sc.nextLine();

        // Create salt
        SecureRandom random = new SecureRandom();
        byte[] salt = new byte[16];
        random.nextBytes(salt);

        // Hash password with salt
        byte[] hash;
        hash = getHashedValue(passWord, salt);

        // Print result
        System.out.println("Username: " + userName);
        System.out.println("Password: " + Arrays.toString(hash));
    }

    private static byte[] getHashedValue(String passWord, byte[] salt) {
        SecretKeyFactory factory = null;
        try {
            PBEKeySpec spec = new PBEKeySpec(passWord.toCharArray(), salt, 65536, 128);
            factory = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        } catch (NoSuchAlgorithmException e) {
            System.out.println("No Such Algorithm: " + e.getMessage());
        } catch (InvalidKeySpecException e) {
            System.out.println("Invalid Key Spec: " + e.getMessage());
        }
        SecretKey secret = factory.generateSecret(spec);
        byte[] hash = secret.getEncoded();
        return hash;
    }
}