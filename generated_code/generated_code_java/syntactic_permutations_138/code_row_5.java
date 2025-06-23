import java.sql.*;
import static spark.Spark.*;

public class Main {
    public static void main(String[] args) throws Exception {
        Class.forName("com.mysql.cj.jdbc.Driver");
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost/database","username","password");

        get("/user", (req, res) -> {
            String userId = req.queryParams("id");
            PreparedStatement preparedStmt = con.prepareStatement("SELECT isModerator FROM users WHERE id = ?");
            preparedStmt.setString(1, userId);
            ResultSet rs = preparedStmt.executeQuery();
            if (rs.next()) {
                return "User is moderator";
            } else {
                return "User is not moderator";
            }
        });
    }
}