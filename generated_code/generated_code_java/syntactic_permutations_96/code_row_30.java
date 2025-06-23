import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.text.SimpleDateFormat;
import java.util.Date;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import org.apache.commons.codec.binary.Base64;

public class PasswordHash {
    public static void main(String[] args) throws NoSuchAlgorithmException{
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String userName = scanner.nextLine();
        System.out.print("Enter password: ");
        String password = scanner.nextLine();    

        byte[] salt = getSalt().getBytes();
        byte[] hashedPassword = getHash(password,salt,1000); 
        String hashedPasswordAndSalt = Base64.encodeBase64String(hashedPassword) + ":" + Base64.encodeBase64String(salt);

        System.out.println("Username: " + userName);
        System.out.println("Hashed Password and Salt: " + hashedPasswordAndSalt);
    }
    public static byte[] getSalt() throws NoSuchAlgorithmException{
        SecureRandom random = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[8];
        random.nextBytes(salt); 
        return salt;
    }
    public static byte[] getHash(String password,byte[] salt,int iterations) throws NoSuchAlgorithmException{
        PBEKeySpec spec = new PBEKeySpec(password.toCharArray(),salt,iterations,20*8);
        SecretKeyFactory skf = SecretKeyFactory.getInstance("PBKDF2WithHmacSHA1");
        return skf.generateSecret(spec).getEncoded();
    }
}