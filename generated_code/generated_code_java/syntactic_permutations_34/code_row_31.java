package com.company;

import java.sql.*;

public class Main {
    public static void main(String[] args) throws SQLException {
        String username = "john";
        String password = "123456";
        Connection con = getConnection();

        try (Statement statement = con.createStatement()) {
            String sql = "SELECT * FROM user WHERE username = '" + username + "' AND password = '"+password+"'";
            ResultSet resultSet = statement.executeQuery(sql);
            if (!resultSet.next()){
                System.out.println("Username or Password is incorrect");
            } else {
                System.out.println("Welcome " + username);
            }
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            con.close();
        }
    }

    public static Connection getConnection() throws SQLException {
        return DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "");
    }
}