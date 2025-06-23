import java.security.*;
import javax.crypto.*;
import java.util.*;

public class RegistrationPage {
    private static Scanner scanner = new Scanner(System.in);
    private static String username;
    private static String password;
    private static String firstName;
    private static String lastName;
    private static String email;
    public static void main(String[] args) throws NoSuchAlgorithmException, InvalidKeyException {
        System.out.println("Enter your username:");
        username = scanner.nextLine();
        System.out.println("Enter your password:");
        password = scanner.nextLine();
        firstName = scanner.nextLine();
        lastName = scanner.nextLine();
        email = scanner.nextLine();

        // hash the password
        String hashedPassword = hashPassword(password);

        // check if username is in database
        if (usernameInDatabase(username)) {
            System.out.println("Username already exists, please try again.");
        } else {
            // insert username and hashed password into database
            insertUserDetails();
            System.out.println("Registration succeeded!");
        }
    }

    private static String hashPassword(String password) throws NoSuchAlgorithmException, InvalidKeyException {
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());
        return Arrays.toString(hashedPassword);
    }

    private static boolean usernameInDatabase(String username) {
        // check if username is in database
        return false;
    }

    private static void insertUserDetails() {
        // insert username and hashed password into database
    }
}