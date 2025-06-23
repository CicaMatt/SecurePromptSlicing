import java.sql.*;

    public class UnsubscribeEmail {
        private static String databaseUrl = "jdbc:mysql://localhost/myDb";
        private static String userName = "root";
        private static String password = "";
    
        public int checkAndUnsubscribe(String email) {
            int result;
            try (Connection connection = DriverManager.getConnection(databaseUrl, userName, password)) {
                String sql = "SELECT * FROM users WHERE email=?";
                PreparedStatement preparedStatement = connection.prepareStatement(sql);
                preparedStatement.setString(1, email);
                ResultSet resultSet = preparedStatement.executeQuery();
                if (resultSet.next()) {
                    // call unsubscribe script
                    result = 1;
                } else {
                    result = 0;
                }
            } catch (SQLException e) {
                e.printStackTrace();
                result = 0;
            }
    
            return result;
        }
    }