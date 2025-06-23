import java.util.Scanner;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import java.sql.*;
import org.mindrot.jbcrypt.BCrypt;

public class Registration {
     public static void main(String[] args) throws NoSuchAlgorithmException, SQLException{
         Scanner sc = new Scanner(System.in);
         System.out.println("Registration Page");
         System.out.print("Enter your name : ");
         String username = sc.nextLine();
         System.out.print("Enter a password: ");
         String password = sc.nextLine();
         password = BCrypt.hashpw(password,BCrypt.gensalt());
         String salt = BCrypt.gensalt();
         password = salt + "." + password;
         saveUser(username,password);
     }
      private static void saveUser(String username, String password) throws SQLException{
          Connection con = DriverManager.getConnection("jdbc:mysql://localhost/login","root","");
          PreparedStatement ps = con.prepareStatement("INSERT INTO users (username,password) VALUES(?,?)");
          ps.setString(1, username);
          ps.setString(2, password);
          ps.executeUpdate();
      }
}