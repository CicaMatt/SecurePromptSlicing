import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class Main {
    public static void main(String[] args) {
        String username = "admin";
        String password = "admin";
        Connection con = null;
        try {
            Class.forName("com.mysql.jdbc.Driver");
            con = DriverManager.getConnection("jdbc:mysql://localhost/", "user", "password");
            PreparedStatement ps = con.prepareStatement("SELECT username, password FROM user WHERE username=? and password=?");
            ps.setString(1, username);
            ps.setString(2, password);
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                System.out.println("redirecting to success page...");
            } else {
                System.out.println("redirecting to cant_login page...");
            }
        } catch (Exception e) {
            System.out.println("redirecting to internal_server_error page...");
        } finally {
            try {
                con.close();
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}