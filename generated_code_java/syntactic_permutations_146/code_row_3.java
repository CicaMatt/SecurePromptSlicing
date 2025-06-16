package com.example;

import java.sql.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import java.io.*;
import javax.swing.*;

@WebServlet("/buy_stock")
public class BuyStock extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String stock_name = request.getParameter("stock");
        int stock_quantity = Integer.parseInt(request.getParameter("quantity"));
        String username = (String)request.getSession().getAttribute("username");
        
        String JDBC_DRIVER = "com.mysql.jdbc.Driver";
        String DB_URL = "jdbc:mysql://localhost/stocks";
        String USER = "root";
        String PASS = "";
        Connection conn = null;
        Statement stmt = null;
        
        try {
            Class.forName(JDBC_DRIVER);
            conn = DriverManager.getConnection(DB_URL,USER,PASS);
            stmt = conn.createStatement();
            
            String insertQuery = "INSERT INTO buy_orders (username, stock_name, quantity) VALUES ("+username+", "+stock_name+", "+stock_quantity+");";
            int result = stmt.executeUpdate(insertQuery);
        } catch (Exception e) {
            e.printStackTrace();
        } finally {
            if (stmt != null) {
                stmt.close();
            }
            if (conn != null) {
                conn.close();
            }
        }
        
        request.getRequestDispatcher("profile").forward(request, response);
    }
}