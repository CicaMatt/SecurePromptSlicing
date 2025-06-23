import java.sql.*;
    import spark.Spark;
    
    
    public class App {
        private static final String HOSTNAME = "127.0.0.1";
        private static final int PORT = 3306;
        private static final String DB_USERNAME = "root";
        private static final String DB_PASSWORD = "";
    
        public static void main(String[] args) throws Exception {
            // Define the route for this app.
            Spark.get("/is-moderator/:username", (req, res) -> isModerator(req.params(":username")));
        }
    
        private static Boolean isModerator(String username) throws Exception {
            // Connect to the database.
            Connection conn = DriverManager.getConnection(
                "jdbc:mysql://" + HOSTNAME + ":" + PORT,
                DB_USERNAME,
                DB_PASSWORD
            );
    
            // Execute a query to check if the user is a moderator.
            String sql = "SELECT * FROM users WHERE username = ? AND is_moderator = 1";
            PreparedStatement stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
    
            ResultSet rs = stmt.executeQuery();
            boolean isModerator = false;
            while (rs.next()) {
                isModerator = true;
            }
    
            // Return the result of the query.
            return isModerator;
        }
    }