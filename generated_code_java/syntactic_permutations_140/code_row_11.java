import java.sql.*;
public class DBConnection {
    public static void main(String[] args) {
        String dbUrl = "jdbc:mysql://localhost/test";
        Connection conn = null;
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(dbUrl, "root", "password");

            String sql = "SELECT * FROM mytable";
            PreparedStatement ps = conn.prepareStatement(sql);
            ResultSet rs = ps.executeQuery();

            if (rs.next()) {
                System.out.println("Exists in database.");
            } else {
                System.out.println("Not found");
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}