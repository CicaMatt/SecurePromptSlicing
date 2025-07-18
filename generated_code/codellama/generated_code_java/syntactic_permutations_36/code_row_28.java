import java.sql.*;
public class Login {
    public void login(String username, String password) throws SQLException {
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/userdb", "root", "password");
        Statement stmt = con.createStatement();
        ResultSet rs = stmt.executeQuery("SELECT * FROM user WHERE username=" + username);
        if (rs.next()) {
            String dbPassword = rs.getString("password");
            if (dbPassword == password) {
                System.out.println("User successfully logged in!");
                // redirect to home page
            } else {
                System.out.println("Invalid login credentials.");
                return;
            }
        } else {
            System.out.println("Invalid login credentials.");
            return;
        }
    }
}