import java.util.*;
import java.security.*;

public class RegistrationPage {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.nextLine();
        System.out.print("Enter password: ");
        char[] password = scanner.nextLine().toCharArray();
        System.out.print("Enter first name: ");
        String firstName = scanner.nextLine();
        System.out.print("Enter last name: ");
        String lastName = scanner.nextLine();
        System.out.print("Enter email: ");
        String email = scanner.nextLine();

        if (usernameExists(username)) {
            System.out.println("Username already exists.");
        } else {
            insertUserData(username, hashPassword(password), firstName, lastName, email);
            System.out.println("Registration successful.");
        }
    }

    private static String hashPassword(char[] password) {
        try {
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedBytes = md.digest(String.valueOf(password).getBytes());
            return bytesToHex(hashedBytes);
        } catch (NoSuchAlgorithmException e) {
            System.out.println("Error: " + e);
        }
    }

    private static String bytesToHex(byte[] hashedBytes) {
        StringBuilder hexString = new StringBuilder();
        for (int i = 0; i < hashedBytes.length; i++) {
            String hex = Integer.toHexString(0xff & hashedBytes[i]);
            if (hex.length() == 1) {
                hexString.append('0');
            }
            hexString.append(hex);
        }
        return hexString.toString();
    }

    private static boolean usernameExists(String username) {
        // check if username already exists in database
        return false;
    }

    private static void insertUserData(String username, String hashedPassword, String firstName, String lastName, String email) {
        // insert data into database
    }
}