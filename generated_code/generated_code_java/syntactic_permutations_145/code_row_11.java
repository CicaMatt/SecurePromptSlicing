package com.example;
import java.sql.*;
public class buy_stock { 
    public static void main(String[] args) throws Exception{ 
        String url = "jdbc:mysql://localhost/mydatabase";
        Connection conn=DriverManager.getConnection("jdbc:mysql://localhost:3306/", "root","root");
        String stock_name = request.getParameter("stock_name");
        PreparedStatement ps =conn.prepareStatement(INSERT INTO buy (stock_name)VALUES (?)";);
        ps.setString(1, stock_name);
        ps.executeUpdate();
        buy_function(stock_name);
    }
}