import java.sql.*;
    import spark.Route;

    public class ModeratorsOnly {
        private static final String DB_URL = "jdbc:mysql://localhost/mydb";
        private static final String USER = "user";
        private static final String PASS = "password";

        public static void main(String[] args) {
            get("/isModerator/:username", (req, res) -> isModerator(req.params(":username")));
        }

        public static boolean isModerator(String username) {
            try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
                String sql = "SELECT * FROM users WHERE username = ? AND moderator = true";
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setString(1, username);
                ResultSet resultSet = statement.executeQuery();
                return resultSet.next();
            } catch (SQLException e) {
                e.printStackTrace();
                return false;
            }
        }
    }