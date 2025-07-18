import java.sql.*;
import java.util.ArrayList;
import java.security.MessageDigest;
import javax.xml.bind.DatatypeConverter;
public class PasswordHashing {
    public static void main(String[] args) {
        //Declare variables
        ArrayList<User> userList = new ArrayList<>();
        String password;
        byte[] salt;
        MessageDigest md;
        int iterations;
        //Connect to database and table
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/passwordhashing?" + "user=root&password=mysql");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT name, password FROM users WHERE 1");
            while (rs.next()) {
                String name = rs.getString("name");
                String password = rs.getString("password");
                User user = new User(name, password);
                userList.add(user);
                System.out.println("Username: " + name + " Password: " + password);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}