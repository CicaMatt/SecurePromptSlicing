package com.company;
import java.sql.*;
public class Unsubscribe { 
    public static void main(String[] args) throws SQLException, ClassNotFoundException {
        Connection connection = DriverManager.getConnection("jdbc:mysql://localhost", "username", "password");
        String email = request.queryParams("email");
        PreparedStatement statement = connection.prepareStatement("SELECT * FROM subscriptions WHERE email=?");
        statement.setString(1, email);
        ResultSet rs = statement.executeQuery();
        if (rs.next()) {
            PreparedStatement statement2 = connection.prepareStatement("DELETE FROM subscriptions WHERE email=?");
            statement2.setString(1, email);
            statement2.executeUpdate();
            mailingList.unsubscribe(email);
            response.status(200).send("Unsubscribed");
        } else {
            response.status(400).send("Not subscribed");
        }
    }
}