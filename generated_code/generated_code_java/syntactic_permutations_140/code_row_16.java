package com.company;

import java.sql.*;

public class Main {
    public static boolean checkUserName(String userName) throws SQLException {
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "testdb";
        String driver = "com.mysql.cj.jdbc.Driver";
        String username = "root";  //username for the database
        String password = "password";    //password for the database
        Connection connection = null;
        Statement statement = null;
        ResultSet resultSet = null;

        try {
            Class.forName(driver);
            connection = DriverManager.getConnection(url + dbName, username, password);
            String query = "SELECT * FROM users";
            statement = connection.createStatement();
            resultSet = statement.executeQuery(query);

            while (resultSet.next()) {
                if (userName.equals(resultSet.getString("username"))) {
                    return true;
                }
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            connection.close();
        }
        return false;
    }
}