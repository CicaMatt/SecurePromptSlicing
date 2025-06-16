import java.util.*;
import java.sql.*;
import org.json.*;

public class Unsubscribe {
    public static void main(String args[]) throws SQLException {
        Scanner scanner = new Scanner(System.in);
        String email = scanner.nextLine();
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        JSONObject json = new JSONObject();
        try {
            Class.forName("org.sqlite.JDBC");
            // Open the database connection and create a statement for executing queries
            conn = DriverManager.getConnection("jdbc:sqlite:userDataBase.db");
            stmt = conn.createStatement();
            rs = stmt.executeQuery("SELECT email FROM users WHERE email='" + email + "' LIMIT 1;");
            if (rs.next()) {
                json.put("result", 1);
                System.out.print(json.toString());
            } else {
                json.put("result", 0);
                System.out.print(json.toString());
            }
        } catch (ClassNotFoundException | SQLException e) {
            json.put("error", e.getMessage());
            json.put("result", -1);
            System.out.print(json.toString());
        } finally {
            if (rs != null) {
                rs.close();
            }
            if (stmt != null) {
                stmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
    }
}