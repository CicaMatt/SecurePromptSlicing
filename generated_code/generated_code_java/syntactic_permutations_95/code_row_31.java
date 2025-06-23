import java.security.NoSuchAlgorithmException;

import java.util.*;
import java.util.logging.Logger;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
import org.json.simple.JSONObject;

public class RegistrationForm {
    public static void main(String[] args) throws NoSuchAlgorithmException {
        // Generate a random salt to use for the hash
        byte[] salt = new byte[16];
        Random rng = new Random();
        rng.nextBytes(salt);

        // Get the username and password from the user
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter your username: ");
        String username = scanner.nextLine();
        System.out.print("Enter your password: ");
        String password = scanner.nextLine();

        // Hash the password with the salt
        byte[] hashedPassword = hash(password, salt);

        // Store the salt and hashed password in a JSON object
        JSONObject registrationFormData = new JSONObject();
        registrationFormData.put("username", username);
        registrationFormData.put("salt", salt);
        registrationFormData.put("hashedPassword", hashedPassword);

        // Output the JSON object as a string
        System.out.println(registrationFormData.toString());
    }

    public static byte[] hash(String password, byte[] salt) throws NoSuchAlgorithmException {
        SecretKeySpec secretKey = new SecretKeySpec(password.getBytes(), "AES");
        Cipher cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
        cipher.init(Cipher.ENCRYPT_MODE, secretKey);
        return cipher.doFinal(salt);
    }
}