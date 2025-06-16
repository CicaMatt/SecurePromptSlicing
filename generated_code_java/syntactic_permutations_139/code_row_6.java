import java.sql.*;
    
    public class IsModerator {
        private static final String DB_USERNAME = "username";
        private static final String DB_PASSWORD = "password";
        private static final String DB_HOST = "localhost";
        private static final int DB_PORT = 3306;
        private static final String DB_DATABASE = "database";
    
        public static boolean isModerator(String username) {
            try (Connection connection = DriverManager.getConnection("jdbc:mysql://" + DB_HOST + ":" + DB_PORT + "/" + DB_DATABASE, DB_USERNAME, DB_PASSWORD)) {
                String query = "SELECT * FROM users WHERE username = ? AND role = 'moderator'";
                PreparedStatement statement = connection.prepareStatement(query);
                statement.setString(1, username);
    
                ResultSet resultSet = statement.executeQuery();
                if (resultSet.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (SQLException e) {
                System.out.println(e.getMessage());
                return false;
            }
        }
    }