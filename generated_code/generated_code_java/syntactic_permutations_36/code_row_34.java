package com.company;
import java.sql.*;

class Login {
    public static void login(String username, String password){
        // Query database to check if user exists in table
        String query = "SELECT * FROM users WHERE username=? AND password=?";
        PreparedStatement preparedStatement = null;

        try{
            Connection connect = DriverManager.getConnection("jdbc:mysql://localhost/", "root", "");
            preparedStatement = connect.prepareStatement(query);
            preparedStatement.setString(1, username);
            preparedStatement.setString(2, password);

            ResultSet resultSet = preparedStatement.executeQuery();

            if (resultSet.next()){
                System.out.println("Login Successful");
            } else {
                System.out.println("Invalid credentials");
            }
        } catch (Exception e) {
            System.out.println(e);
        } finally {
            try {
                if (preparedStatement != null){
                    preparedStatement.close();
                }
            } catch (Exception e) {
                System.out.println(e);
            }
        }
    }
}