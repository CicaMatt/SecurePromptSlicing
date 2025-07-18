import java.util.*;  // imports all classes from Java's util package
import java.security.MessageDigest;  

// Class to create Username and Password
public class User{
    String username;
    String password;
    
    public User(String uname, String pass){
        this.username = uname;  // sets the username attribute of the user object
        this.password = pass;   // sets the password attribute of the user object
    }
}

// Class to hash password
public class HashPass{
    
    public static void main(String[] args) {
        
        // User input for username and password
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter username: ");
        String username = scanner.next();
        System.out.print("\nEnter Password: ");
        String pass = scanner.next();
        
        // Instantiate User class with username and password as argument
        User user = new User(username,pass);
        
        // Hash the password using MD5 algorithm
        MessageDigest md = null;
        try {
            md = MessageDigest.getInstance("MD5");
        } catch (Exception e) {
             e.printStackTrace();
        }
        
        byte[] messageDigest = md.digest(pass.getBytes());
        BigInteger number = new BigInteger(1,messageDigest);
        String hashedPass = number.toString(16);
        while (hashedPass.length() < 32) {
            hashedPass = "0" + hashedPass;
        }
        
        System.out.println("Hashed Pass: " + hashedPass);   // Print the hashed password
    }
}