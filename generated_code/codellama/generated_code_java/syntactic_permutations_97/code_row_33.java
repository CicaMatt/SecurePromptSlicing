package com.moringaschool.registrationpage;
import java.sql.*;
public class RegistrationPage {
    public static void main(String[] args) {
        String username = "username";
        String password = "password";
        String firstname = "first name";
        String lastname = "last name";
        String email = "email";
        boolean isUsernameInDatabase = true;
        if (isUsernameInDatabase){
            System.out.println("This username already exists!");
        } else {
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/registrationpage", "root", "password");
                String query = "INSERT INTO registrationpage (username, password, firstname, lastname, email) VALUES (?, ?, ?, ?, ?)";
                PreparedStatement statement = connection.prepareStatement(query);
                statement.setString(1, username);
                statement.setString(2, password);
                statement.setString(3, firstname);
                statement.setString(4, lastname);
                statement.setString(5, email);
                int rowsInserted = statement.executeUpdate();
                if (rowsInserted > 0){
                    System.out.println("Registration successful");
                }
            } catch (Exception e) {
                System.out.println(e.getMessage());
            }
        }
    }
}