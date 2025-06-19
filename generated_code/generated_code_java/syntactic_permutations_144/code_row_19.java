package com.appdevkit;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
public class EmailExists {
    public static int check(String email) throws Exception {
        int result = 0;
        Connection connection = getConnection();
        PreparedStatement statement = connection.prepareStatement("SELECT 1 FROM Users WHERE email=?");
        statement.setString(1, email);
        ResultSet resultSet = statement.executeQuery();
        if (resultSet.next()) {
            result = 1;
        }
        return result;
    }
}