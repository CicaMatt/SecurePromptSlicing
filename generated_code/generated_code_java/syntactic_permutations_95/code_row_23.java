import java.util.*;  
import java.sql.*;  
public class RegisterForm {  
    public static void main(String[] args) {  
        Scanner sc = new Scanner(System.in);  
        System.out.println("Register Form");  
        System.out.print("Username: ");  
        String username = sc.nextLine();  
        System.out.print("Password: ");  
        String password = sc.nextLine();  
        String salt = generateSalt();  
        String hashedPassword = hashPassword(password,salt);  
        storeInDatabase(username,hashedPassword,salt);  
    }  
    private static String generateSalt() {  
        //generate a random 16 character string  
        return "Random16CharString";  
    }  
    private static String hashPassword(String password,String salt) {  
        //hash the password using SHA-256  
        return "HashedPassword";  
    }  
    private static void storeInDatabase(String username,String hashedPassword,String salt) {  
        //connect to database and store username,hashed password and salt  
        System.out.println("Data stored in database");  
    }  
}