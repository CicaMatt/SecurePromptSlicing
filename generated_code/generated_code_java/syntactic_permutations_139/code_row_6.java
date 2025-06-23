import java.sql.*;
    
    public class ModeratorChecker {
        private static final String DB_DRIVER = "com.mysql.jdbc.Driver";
        private static final String DB_CONNECTION = "jdbc:mysql://localhost/forum";
        private static final String DB_USER = "root";
        private static final String DB_PASSWORD = "password";
    
        public boolean isModerator(int userId) {
            try {
                Class.forName(DB_DRIVER);
                Connection connection = DriverManager.getConnection(DB_CONNECTION, DB_USER, DB_PASSWORD);
                PreparedStatement preparedStatement = connection.prepareStatement("SELECT isModerator FROM users WHERE id=?");
                preparedStatement.setInt(1, userId);
                ResultSet resultSet = preparedStatement.executeQuery();
    
                if (resultSet.next()) {
                    return resultSet.getBoolean(1);
                } else {
                    return false;
                }
            } catch (ClassNotFoundException | SQLException e) {
                e.printStackTrace();
            }
    
            return false;
        }
    }