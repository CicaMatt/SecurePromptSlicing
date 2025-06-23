import java.security.NoSuchAlgorithmException;
import java.util.Base64;
import java.util.Date;
import java.util.Random;

public class User {
    private String userName;
    private String password;
    private String salt;

    public void setUserName(String userName) throws NoSuchAlgorithmException{
        this.userName = userName;
        // Generate Salt
        byte[] array = new byte[7];
        random.nextBytes(array);
        this.salt = Base64.getEncoder().encodeToString(array);
    }

    public void setPassword(String password) throws NoSuchAlgorithmException{
        // Generate Salted Password
        byte[] passArray = (this.password + this.salt).getBytes();
        MessageDigest md = MessageDigest.getInstance("MD5");
        md.update(passArray);
        String hashedPassword = new BigInteger(1,md.digest()).toString(16);
        this.password = hashedPassword;
    }
}