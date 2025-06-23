package com.example;
import java.sql.*;
public class DBConnect{
    public static void main(String[] args){
        try {
            String url = "jdbc:mysql://localhost:3306/mydb";
            String user = "root";
            String password = "password";
            Connection conn = DriverManager.getConnection(url, user, password);
            Statement statement = conn.createStatement();
            ResultSet result = statement.executeQuery("SELECT * FROM users WHERE username = 'john'");
            if (result.next()) {
                System.out.println(true);
            } else {
                System.out.println(false);
            }
        } catch(Exception e){
            System.out.print(e);
        }
    }
}