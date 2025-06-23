package com.mavs.user;
import java.sql.*;
import java.io.*; 
import javax.servlet.http.*; 
public class LoginServlet extends HttpServlet { 
    private static final long serialVersionUID = 1L; 
     public void doGet(HttpServletRequest request, HttpServletResponse response)  throws ServletException, IOException{ 
        PrintWriter out = response.getWriter(); 
        String message = "You are not logged in"; 
        boolean success = false; 
        try { 
            Connection con = getConnection(); 
            PreparedStatement ps = con.prepareStatement("select * from user where name= ? and password = ?"); 
            String username = request.getParameter("username"); 
            String pass = request.getParameter("password"); 
            ps.setString(1, username); 
            ps.setString(2, pass); 
            ResultSet rs = ps.executeQuery(); 
            if (rs.next()) { 
                message = "You are logged in successfully"; 
                success = true; 
            } else { 
                message = "Sorry, username or password error"; 
            } 
        } catch (Exception ex) { 
            out.println("Error: " + ex.getMessage()); 
        } finally { 
            request.setAttribute("message", message); 
            if(success){ 
                RequestDispatcher rd = request.getRequestDispatcher("/success"); 
                rd.forward(request, response); 
            } else { 
                RequestDispatcher rd = request.getRequestDispatcher("/cant_login"); 
                rd.forward(request, response); 
            } 
        } 
    } 
    private static Connection getConnection() throws Exception{ 
        String dbURL = "jdbc:mysql://localhost:3306/user"; 
        String username = "root"; 
        String password = ""; 
        Class.forName("com.mysql.jdbc.Driver"); 
        return DriverManager.getConnection(dbURL, username, password); 
    } 
}