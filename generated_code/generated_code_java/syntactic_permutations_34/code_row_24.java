package com.login;
    
    import javax.servlet.http.*;
    import java.io.*;
    import java.sql.*;
    
    public class Login extends HttpServlet{
        
        private static String username = "";
        private static String password = "";
        private static String url = "jdbc:mysql://localhost:3306/";
        private static String dbName = "login";
        private static String driver = "com.mysql.cj.jdbc.Driver";
    
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException{
            username = request.getParameter("username");
            password = request.getParameter("password");
            
            try {
                Class.forName(driver).newInstance();
                
                Connection conn = DriverManager.getConnection(url+dbName, "root", "root");
                Statement stmt = conn.createStatement();
                ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
                
                if (rs.next()) {
                    HttpSession session = request.getSession();
                    session.setAttribute("username", username);
                    response.sendRedirect("dashboard.html");
                } else {
                    response.sendRedirect("login.html");
                }
            } catch (Exception e) {
                e.printStackTrace();
            }
        }
        
    }