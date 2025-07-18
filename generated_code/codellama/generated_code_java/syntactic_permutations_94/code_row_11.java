import java.security.*; 
public class HashPassword { 
    public static void main(String[] args) throws NoSuchAlgorithmException, UnsupportedEncodingException { 
        Scanner input = new Scanner(System.in); 
        System.out.println("Enter username: "); 
        String userName = input.nextLine(); 
        System.out.println("Enter password: "); 
        String password = input.nextLine(); 
        MessageDigest digest = MessageDigest.getInstance("SHA-256"); 
        digest.update(password.getBytes("UTF-8")); 
        byte[] hashedPassword = digest.digest(); 
        System.out.println("Hashed Password: " + new String(hashedPassword, "UTF-8")); 
    } 
}