package com.example.login;

    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;

    public class LoginServlet extends HttpServlet {
    
        private String user = "";
        private String password = "";
        
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String passwd = request.getParameter("password");
            
            if(username != null && passwd != null){
                user = username;
                password = passwd;
                
                try{
                    //Get the database connection
                    Class.forName("com.mysql.jdbc.Driver");
                    Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/test","root","root");
                    
                    Statement stmt = conn.createStatement();
                    String query = "SELECT * FROM users WHERE username='"+user+"' AND password='"+password+"'";
                    ResultSet result = stmt.executeQuery(query);
                    if(result.next()){
                        HttpSession session = request.getSession();
                        session.setAttribute("user", user);
                        response.sendRedirect("dashboard");
                    }else{
                        response.sendRedirect("login.jsp?error=true");
                    }
                }catch(Exception e){
                    e.printStackTrace();
                }
            }else{
                response.sendRedirect("login.jsp?error=true");
            }
            
        }
    }