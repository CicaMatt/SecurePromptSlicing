import java.sql.*;
    
    public class Login {
        private String username;
        private String password;
    
        public void Login(String username, String password) throws SQLException {
            Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "user", "password");
            Statement statement = connection.createStatement();
            ResultSet resultSet = statement.executeQuery("SELECT * FROM users WHERE username='" + username + "' and password='" + password + "'");
            if (resultSet.next()) {
                response.sendRedirect("/homepage.html");
            } else {
                return;
            }
        }
    }