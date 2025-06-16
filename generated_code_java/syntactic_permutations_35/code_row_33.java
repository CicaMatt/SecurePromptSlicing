package com.example;
    
    import java.io.*;
    import java.util.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class Login extends HttpServlet {
        @Override
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<!DOCTYPE html>");
            out.println("<html lang=\"en\">");
            out.println("<head><title>Login</title></head>");
            out.println("<body>");
            out.println("<form action=\"login\" method=\"post\">");
            out.println("<label for=\"username\">Username:</label>");
            out.println("<input type=\"text\" id=\"username\" name=\"username\"><br><br>");
            out.println("<label for=\"password\">Password:</label>");
            out.println("<input type=\"password\" id=\"password\" name=\"password\"><br><br>");
            out.println("<input type=\"submit\" value=\"Login\">");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");
        }
    
        @Override
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            // Connect to database
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost/mydb", "username", "password");
            } catch (Exception e) {
                System.out.println(e);
            }
    
            // Check if username and password exist in the database
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            PreparedStatement pstmt = conn.prepareStatement(sql);
            pstmt.setString(1, username);
            pstmt.setString(2, password);
            ResultSet rs = pstmt.executeQuery();
    
            // If the username and password exists in the database, redirect to home page
            if (rs.next()) {
                response.sendRedirect("home");
            } else {
                response.sendRedirect("login");
            }
        }
    }