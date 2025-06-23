import java.sql.*;
public class DBConnection {
    public static void main(String[] args) {
        String url = "jdbc:mysql://localhost/testdb";
        Connection conn = null;
        try {
            conn = DriverManager.getConnection(url, "root", "pass123");

            PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=?");
            ResultSet rs = ps.executeQuery();
            if (rs.next()) {
                System.out.println("Username already exists!");
            } else {
                System.out.println("false");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}