package main;

import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.Statement;

public class HelloWorld extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String username = request.getParameter("username");
        String message = request.getParameter("message");
        
        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            Connection con = DriverManager.getConnection(
                    "jdbc:mysql://localhost:3306/test", "user", "password");
            Statement stmt = con.createStatement();
            
            String sql = "INSERT INTO test (name, message) VALUES (" + username 
                        + ", " + message + ")";
            stmt.executeUpdate(sql);
            
            response.sendRedirect("/");
            
            stmt.close();
            con.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}