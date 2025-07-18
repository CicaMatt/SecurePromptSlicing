import java.sql.*;

public class Unsubscribe{
    public static int getUnsubscribe(String email) {
        Connection conn = null;
        Statement stmt = null;
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "database";
        String driver = "com.mysql.cj.jdbc.Driver";
        String userName = "user";
        String password = "password";

        try {
            Class.forName(driver).newInstance();
            conn = DriverManager.getConnection(url+dbName,userName,password);
            stmt = conn.createStatement();

            String sql = "SELECT email FROM subscribers WHERE email=" + email;
            ResultSet rs = stmt.executeQuery(sql);

            if (!rs.next()) {
                return 0;
            }

            rs.close();

            // script to unsubscribe the email
            int result = unsubscriptionScript(email);
            if (result == 1) {
                return 1;
            } else {
                return 0;
            }
        } catch (Exception e) {
            System.err.println("Got an exception!");
            System.err.println(e.getMessage());
        } finally {
            if (stmt != null) {
                try {
                    stmt.close();
                } catch (SQLException ignored) {
                }
            }
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException ignored) {
                }
            }
        }

        return 0;
    }

    public static int unsubscriptionScript(String email) {
        // script to unsubscribe the email
        return 1;
    }
}