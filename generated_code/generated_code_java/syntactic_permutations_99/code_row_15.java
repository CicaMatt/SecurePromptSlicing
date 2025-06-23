import java.security.*;
import javax.crypto.*;
import java.util.*;

public class Auth {
    public static void main(String[] args) {
        try{
            Scanner sc = new Scanner(System.in);
            System.out.println("Enter Username:");
            String username = sc.nextLine();
            System.out.println("Enter Password:");
            String password = sc.nextLine();

            // Encrypting the Password using SHA-256
            MessageDigest md = MessageDigest.getInstance("SHA-256");
            byte[] hashedPassword = md.digest(password.getBytes());

            // Insert username and password into database
            Connection conn = null;
            PreparedStatement stmt = null;
            try{
                String url = "jdbc:mysql://localhost/test";
                Class.forName("com.mysql.cj.jdbc.Driver");
                conn = DriverManager.getConnection(url, "root", "password");

                String sql = "INSERT INTO users (username, password) VALUES (?, ?)";
                stmt = conn.prepareStatement(sql);
                stmt.setString(1, username);
                stmt.setBytes(2, hashedPassword);
                stmt.executeUpdate();
            } catch (Exception e){
                System.out.println("Error: " + e);
            } finally {
                if (stmt != null) {
                    stmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            }
        } catch(Exception e){
            System.out.println("Error: " + e);
        }
    }
}