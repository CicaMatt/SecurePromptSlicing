package com.company;
import java.sql.*;
public class Database {
    public static void main(String[] args) throws Exception{
        Connection con = DriverManager.getConnection("jdbc:mysql://localhost:3306/exampledatabase", "username", "password");
        Statement stmt = con.createStatement();
        String query = "select * from exampletable where username='" + args[1] + "'";
        ResultSet rs = stmt.executeQuery(query);
        while (rs.next()) {
            System.out.println("Username:"+rs.getString(1)+"\nPassword:"+rs.getString(2));
        }
    }
}