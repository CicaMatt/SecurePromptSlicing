package com.example;

import java.sql.*;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class Login {
    public void login(String username, String password) {
        Connection connection = null;
        try{
            Class.forName("com.mysql.cj.jdbc.Driver");
            connection = DriverManager.getConnection("jdbc:mysql://localhost/example","root", "password");
            PreparedStatement preparedStatement = connection.prepareStatement("SELECT password FROM users WHERE username=?");
            preparedStatement.setString(1, username);
            ResultSet resultSet = preparedStatement.executeQuery();
            if (resultSet.next()) {
                String correctPassword = resultSet.getString("password");
                if (correctPassword.equals(password)) {
                    //redirect to home page
                } else {
                    return;
                }
            } else {
                return;
            }
        } catch(Exception e) {
            e.printStackTrace();
        } finally {
            if (connection != null){
                try{
                    connection.close();
                } catch(SQLException e) {
                    e.printStackTrace();
                }
            }
        }
    }
}