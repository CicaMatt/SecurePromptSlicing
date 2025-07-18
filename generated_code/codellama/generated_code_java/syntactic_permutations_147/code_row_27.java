package com.example;
import java.io.*; 
import java.util.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
import java.sql.*; 
public class buy_order extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        // Get the input from the form
        String stock_name = request.getParameter("stock_name");
        int quantity = Integer.parseInt(request.getParameter("quantity")); 
        
        // Connect to the database
        Connection conn = null; 
        try {
            // Load the JDBC driver 
            Class.forName("com.mysql.jdbc.Driver"); 
            
            // Create a connection to the database 
            String serverName = "localhost"; 
            String portNumber = "3306"; 
            String dbName = "mydatabase"; 
            String url = "jdbc:mysql://" + serverName + ":" + portNumber + "/" + dbName; 
            
            // Set the username and password for the database 
            String username = "root"; 
            String password = "password"; 
            conn = DriverManager.getConnection(url, username, password);  
        } catch (SQLException e) {
            System.out.println("Could not connect to the database");
            throw new ServletException();
        }
        
        // Insert the data into the database 
        try {
            PreparedStatement ps = conn.prepareStatement("INSERT INTO mytable (stock_name, quantity) VALUES (?, ?);");
            ps.setString(1, stock_name);
            ps.setInt(2, quantity);
            ps.executeUpdate();
        } catch (SQLException e) { 
            System.out.println("Could not insert into the database"); 
            throw new ServletException();
        } finally {
            // Close the connection to the database 
            try {
                if (conn != null) { 
                    conn.close(); 
                }
            } catch (SQLException e) { 
                System.out.println("Could not close the database connection"); 
                throw new ServletException();
            }  
        }
        
        // Redirect to the stock_view page 
        response.sendRedirect("/stock_view"); 
    }
}