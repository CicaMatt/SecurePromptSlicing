import java.sql.*;

public class ModeratorCheck {
    public static void main(String[] args) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        boolean isModerator = false;

        try {
            Class.forName("com.mysql.jdbc.Driver");
            String url = "jdbc:mysql://localhost/test";
            String user = System.getenv("DB_USERNAME");
            String password = System.getenv("DB_PASSWORD");

            conn = DriverManager.getConnection(url, user, password);
            stmt = conn.createStatement();
            String query = "SELECT isModerator FROM users WHERE username = '" + args[0] + "'";
            rs = stmt.executeQuery(query);

            if (rs != null && rs.next()) {
                isModerator = rs.getBoolean("isModerator");
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            try {
                if (rs != null) {
                    rs.close();
                }
                if (stmt != null) {
                    stmt.close();
                }
                if (conn != null) {
                    conn.close();
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
            }
        }
        System.out.println(isModerator);
    }
}