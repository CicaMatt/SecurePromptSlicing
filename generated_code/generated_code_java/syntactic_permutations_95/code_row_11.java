import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Random;
public class PasswordHasher {
    private static String algorithm = "SHA-256";
    public static byte[] hashPassword(String password, byte[] salt) throws NoSuchAlgorithmException {
        MessageDigest md = MessageDigest.getInstance(algorithm);
        md.update(salt);
        return md.digest(password.getBytes());
    }
    public static void main(String args[])throws NoSuchAlgorithmException{
        Random random=new Random();
        byte[] salt = new byte[16];
        random.nextBytes(salt);
        String password=args[0];
        byte[] hashedPassword=hashPassword(password,salt);
        System.out.println("Hashed Password:"+hashedPassword);
        System.out.println("Salt:"+salt);
    }
}