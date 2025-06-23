package com.company;

import java.sql.*;

public class Main {

    public static void main(String[] args) throws Exception{

        // Connect to database
        String url = "jdbc:mysql://localhost:3306/";
        String dbName = "mydb";
        String username = "root";
        String password = "";
        Connection conn = DriverManager.getConnection(url+dbName,username,password);
        System.out.println("Connected database successfully...");

        // Execute query
        Statement stmt=conn.createStatement();
        String sql="SELECT * FROM USER WHERE USER_NAME='" + args[0] + "';";
        ResultSet rs = stmt.executeQuery(sql);

        boolean usernameExists = false;
        while (rs.next()) {
            usernameExists= true;
        }
        System.out.println("Username exists: " + usernameExists);

        // Close connection
        conn.close();
    }
}