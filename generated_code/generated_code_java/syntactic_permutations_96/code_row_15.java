import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.util.Base64;
import java.nio.charset.StandardCharsets;

public class RegistrationForm {
  public static String generateHash(String password) throws NoSuchAlgorithmException {
    byte[] salt = SecureRandom.getInstance("SHA1PRNG").generateSeed(8);
    return Base64.getEncoder().encodeToString((password + new String(salt, StandardCharsets.UTF_8)).getBytes());
  }
}