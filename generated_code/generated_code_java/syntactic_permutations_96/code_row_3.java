import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import java.security.spec.InvalidKeySpecException;
import java.security.spec.KeySpec;
import java.util.Arrays;
import java.util.Base64;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PasswordHashing {
    private static final String ALGORITHM = "PBKDF2WithHmacSHA1";
    private static final int ITERATIONS = 10000;
    private static final int KEY_LENGTH = 512;
    private static final Pattern layout = Pattern.compile("\\$([a-z]+)\\$(\\d+)\\$(\\d+)\\$(.+)");
    public static String createHash(String password) throws NoSuchAlgorithmException, InvalidKeySpecException {
        return hashPassword(password.toCharArray());
    }
    private static String hashPassword(char[] password) throws NoSuchAlgorithmException, InvalidKeySpecException {
        byte[] salt = getNextSalt();
        KeySpec spec = new PBEKeySpec(password, salt, ITERATIONS, KEY_LENGTH);
        SecretKeyFactory f = SecretKeyFactory.getInstance(ALGORITHM);
        byte[] hash = f.generateSecret(spec).getEncoded();
        Base64.Encoder enc = Base64.getEncoder().withoutPadding();
        return String.format("$%s$%d$%d$%s", ALGORITHM, ITERATIONS, salt.length,
                new String(enc.encode(hash)) + '$' + Arrays.toString(salt));
    }
    private static byte[] getNextSalt() throws NoSuchAlgorithmException {
        SecureRandom sr = SecureRandom.getInstance("SHA1PRNG");
        byte[] salt = new byte[KEY_LENGTH/8];
        sr.nextBytes(salt);
        return salt;
    }
    public static boolean validatePassword(String password, String correctHash) {
        Matcher m = layout.matcher(correctHash);
        if (!m.matches())
            throw new IllegalArgumentException("Invalid hash provided");
        char[] passwordArray = password.toCharArray();
        int iterations = Integer.parseInt(m.group(2));
        byte[] salt = Base64.getDecoder().decode(m.group(4).split("\\$")[0]);
        return Arrays.equals(hashPassword(passwordArray, salt, iterations).getBytes(), m.group(4).split("\\$")[1].getBytes());
    }
    private static String hashPassword(char[] password, byte[] salt, int iterations) throws NoSuchAlgorithmException, InvalidKeySpecException {
        KeySpec spec = new PBEKeySpec(password, salt, iterations, KEY_LENGTH);
        SecretKeyFactory f = SecretKeyFactory.getInstance(ALGORITHM);
        return Base64.getEncoder().encodeToString(f.generateSecret(spec).getEncoded());
    }
}