import java.security.MessageDigest;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.util.Scanner;
import javax.xml.bind.DatatypeConverter;
import java.sql.ResultSet;

public class Registration {
    public static void main(String[] args) throws Exception{
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter your username: ");
        String username = sc.next();
        System.out.print("Enter your password: ");
        String password = sc.next();
        System.out.print("Enter your first name: ");
        String fname = sc.next();
        System.out.print("Enter your last name: ");
        String lname = sc.next();
        System.out.print("Enter your email address: ");
        String email = sc.next();
        
        MessageDigest md = MessageDigest.getInstance("SHA-256");
        byte[] hashedPassword = md.digest(password.getBytes());
        String passwordHashed = DatatypeConverter.printHexBinary(hashedPassword);

        Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/mydb", "root", "");
        
        String sql = "SELECT * FROM users WHERE username=?";
        PreparedStatement pstm = conn.prepareStatement(sql);
        pstm.setString(1, username);
        ResultSet rs = pstm.executeQuery();
        
        if (rs.next()) {
            System.out.println("Username already exists");
        } else {
            sql = "INSERT INTO users(username, password, firstname, lastname, email) VALUES(?,?,?,?,?)";
            pstm = conn.prepareStatement(sql);
            pstm.setString(1, username);
            pstm.setString(2, passwordHashed);
            pstm.setString(3, fname);
            pstm.setString(4, lname);
            pstm.setString(5, email);
            
            int i = pstm.executeUpdate();
            if (i > 0) {
                System.out.println("Registration successful");
            } else {
                System.out.println("Registration failed");
            }
        }
    }
}