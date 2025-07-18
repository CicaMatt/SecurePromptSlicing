import java.util.*;
import java.security.MessageDigest;
import java.math.BigInteger;

public class RegistrationForm {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.println("Username: ");
        String username = sc.nextLine();
        System.out.println("Password: ");
        String password = sc.nextLine();

        //Hash the password using SHA-512.
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] hashedPasswordBytes = md.digest(password.getBytes());
        StringBuffer sb = new StringBuffer();
        for (byte b : hashedPasswordBytes) {
            sb.append(Integer.toString((b & 0xff) + 0x100, 16).substring(1));
        }
        String hashedPassword = sb.toString();

        System.out.println("Username: " + username);
        System.out.println("Hashed password: " + hashedPassword);
    }
}