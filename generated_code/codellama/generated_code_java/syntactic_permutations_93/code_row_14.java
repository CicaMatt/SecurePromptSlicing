import java.security.*;
import java.sql.*;
import javax.crypto.*;
public class Main {
    public static void main(String[] args) throws Exception {
        Scanner sc = new Scanner(System.in);
        System.out.print("Enter username: ");
        String user = sc.nextLine();
        System.out.print("Enter password: ");
        String pass = sc.nextLine();
        byte[] salt = {
            (byte)0xc7,
            (byte)0x73,
            (byte)0x21,
            (byte)0x8c,
            (byte)0x7e,
            (byte)0xc8,
            (byte)0xee,
            (byte)0x99
        };
        MessageDigest md = MessageDigest.getInstance("SHA-512");
        md.update(pass.getBytes());
        byte[] hashedPassword = md.digest(salt);
        String password = new String(hashedPassword, "UTF-8");
        Connection con = DriverManager.getConnection("jdbc:sqlite:passwords.db");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username = '" + user + "' AND password = '" + password + "';");
        if (rs.next()) {
            System.out.println("Login successful.");
        } else {
            System.out.println("Incorrect username or password.");
        }
    }
}