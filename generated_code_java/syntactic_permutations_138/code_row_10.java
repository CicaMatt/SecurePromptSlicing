import java.sql.*;
import spark.Spark;

public class ModeratorCheck {
    public static void main(String[] args) throws Exception {
        Spark.get("/", (req, res) -> checkModerator());
    }

    private static String checkModerator() {
        try {
            Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "username", "password");
            Statement stmt = conn.createStatement();
            ResultSet rs = stmt.executeQuery("select * from users where moderator = true;");
            while (rs.next()) {
                return rs.getString(1);
            }
        } catch (SQLException ex) {
            System.out.println("An error occurred. " + ex.getMessage());
        }
    }
}