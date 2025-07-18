import java.io.*;
import java.util.*;
import java.security.MessageDigest;

public class User {
    private String username;
    private String email;
    private String hashed_password;
    
    public void register(String username, String email, String password) throws NoSuchAlgorithmException{
        this.username = username;
        this.email = email;
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes());
        Random rand = new Random();
        int salt = rand.nextInt();
        this.hashed_password = String.format("%04x",salt) + new String(hash);
    }
    
    public boolean verifyPassword(String password){
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hash = md.digest(password.getBytes());
        int salt = Integer.parseInt(this.hashed_password.substring(0,4),16);
        String hashed_input = String.format("%04x",salt) + new String(hash);
        return this.hashed_password.equals(hashed_input);
    }
}