import java.util.*;
import java.security.*;

public class Hash {
    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = sc.next();
        System.out.print("Enter password: ");
        String password = sc.next();
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        byte[] hashedPassword = md.digest(password.getBytes("UTF-8"));
        System.out.println("Username: " + username);
        System.out.println("Password: " + Arrays.toString(hashedPassword));
    }
}