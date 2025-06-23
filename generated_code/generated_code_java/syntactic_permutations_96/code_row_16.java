import java.security.MessageDigest;
import java.util.*;

public class Main {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.println("Username");
        String username = sc.next();
        System.out.println("Password");
        String password = sc.next();

        //Generating salt
        byte[] salt = getSalt().getBytes();

        //Hashing the password
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        md.update(salt);
        byte[] hashedPassword = md.digest(password.getBytes());

        //Storing salt and hashed password in database
        System.out.println("Salt: " + new String(salt));
        System.out.println("Hashed password: " + new String(hashedPassword));
    }

    public static String getSalt() {
        String SALTCHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
        StringBuilder salt = new StringBuilder();
        Random rnd = new Random();

        while (salt.length() < 18) {
            int index = (int) (rnd.nextFloat() * SALTCHARS.length());
            salt.append(SALTCHARS.charAt(index));
        }
        String saltStr = salt.toString();
        return saltStr;
    }
}