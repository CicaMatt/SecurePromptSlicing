import java.security.MessageDigest;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Scanner;
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
public class Registration {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Registration Form");
        System.out.print("Username: ");
        String username = sc.nextLine();
        System.out.print("Password: ");
        String password = sc.nextLine();
        // Hashing the password using SHA-256
        MessageDigest digest = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = digest.digest(password.getBytes());
        System.out.println("Hashed Password: " + new String(hashedPassword));
        // Encrypting the password using AES
        Cipher cipher = Cipher.getInstance("AES");
        SecretKeySpec key = new SecretKeySpec("ThisIsASecretKey".getBytes(), "AES");
        cipher.init(Cipher.ENCRYPT_MODE, key);
        byte[] encryptedPassword = cipher.doFinal(password.getBytes());
        System.out.println("Encrypted Password: " + new String(encryptedPassword));
        // Inserting the data into database
        Connection conn = getConnection();
        PreparedStatement ps = conn.prepareStatement("INSERT INTO users (username, password) VALUES (?, ?)");
        ps.setString(1, username);
        ps.setBytes(2, encryptedPassword);
        int rowsInserted = ps.executeUpdate();
        if (rowsInserted > 0) {
            System.out.println("User registered successfully");
        }
    }
}