import java.sql.*;

    public class EmailChecker {
        private static final String URL = "jdbc:mysql://localhost/";
        private static final String USERNAME = "root";
        private static final String PASSWORD = "";
        private static final String DATABASE = "db_name";
    
        public int checkEmail(String email) throws SQLException {
            try (Connection connection = DriverManager.getConnection(URL + DATABASE, USERNAME, PASSWORD);
                 PreparedStatement preparedStatement = connection.prepareStatement("SELECT * FROM emails WHERE email = ?")) {
                preparedStatement.setString(1, email);
    
                ResultSet resultSet = preparedStatement.executeQuery();
    
                if (!resultSet.next()) {
                    return 0;
                }
            }
    
            Unsubscriber unsubscriber = new Unsubscriber();
            int response = unsubscriber.unsubscribeEmail(email);
    
            if (response == 0) {
                return 1;
            } else {
                return 0;
            }
        }
    }