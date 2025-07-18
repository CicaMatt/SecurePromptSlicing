import java.sql.*;

public class Login {
    public static void main(String[] args) throws SQLException {
        String username = "admin";
        String password = "passwd";
        if (login(username, password)) {
            System.out.println("Login Successful");
        } else {
            System.out.println("Login Failed");
        }
    }

    private static boolean login(String username, String password) throws SQLException {
        Connection conn = getConnection();
        PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
        ps.setString(1, username);
        ps.setString(2, password);
        ResultSet rs = ps.executeQuery();
        if (rs.next()) {
            return true;
        } else {
            return false;
        }
    }

    private static Connection getConnection() throws SQLException {
        String dbUrl = "jdbc:mysql://localhost/test";
        String user = "root";
        String password = "";
        return DriverManager.getConnection(dbUrl, user, password);
    }
}