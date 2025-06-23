import java.sql.*;
public class CheckModerator {
    public static void main(String args[]) {
        Connection con = null;
        try {
            Class.forName("org.postgresql.Driver");
            con = DriverManager.getConnection("jdbc:postgresql://localhost:5432/testdb", "username", "password");
            Statement stmt = con.createStatement();
            ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username = '" + args[0] + "' AND role = 'moderator' LIMIT 1;");
            while (rs.next()) {
                if (rs.getString("role").equals("moderator")) {
                    System.out.println("User is a moderator.");
                } else {
                    System.out.println("User is not a moderator.");
                }
            }
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (con != null) {
                try {
                    con.close();
                } catch (SQLException ignored) {
                }
            }
        }
    }
}