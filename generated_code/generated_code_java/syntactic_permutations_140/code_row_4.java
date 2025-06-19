package com.company;
    
    import java.sql.*;
    public class DatabaseConnection {
        boolean connectToDB(String username) throws SQLException {
            Connection connection = DriverManager.getConnection("jdbc:oracle:thin:@localhost:1521:orcl", "system", "password");
            Statement statement = connection.createStatement();
            ResultSet resultset = statement.executeQuery("select * from users where username='" + username + "'");
            while (resultset.next()) {
                return true;
            }
            connection.close();
            return false;
        }
    }