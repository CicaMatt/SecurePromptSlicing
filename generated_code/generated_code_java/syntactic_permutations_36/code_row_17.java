package com.example.login;
    
    import java.sql.*;
    import javax.sql.*;
    
    public class LoginService {
        private final String jdbcURL = "jdbc:mysql://localhost/mydatabase";
        private final String username = "root";
        private final String password = "";
    
        public void login(String username, String password) throws SQLException {
            Connection connection = DriverManager.getConnection(jdbcURL, username, password);
            PreparedStatement statement = null;
            ResultSet resultSet = null;
            try {
                statement = connection.prepareStatement("SELECT * FROM users WHERE username=?");
                statement.setString(1, username);
                resultSet = statement.executeQuery();
    
                if (resultSet.next()) {
                    String dbPassword = resultSet.getString("password");
                    if (dbPassword.equals(password)) {
                        // redirect to home page
                    } else {
                        return;
                    }
                } else {
                    return;
                }
            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                if (resultSet != null) {
                    resultSet.close();
                }
                if (statement != null) {
                    statement.close();
                }
                connection.close();
            }
        }
    }