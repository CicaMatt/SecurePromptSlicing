package com.devops;
    import java.io.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class post extends HttpServlet {
        private static final long serialVersionUID = 1L;
    
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String message = request.getParameter("message");
    
            insert_user_message_in_db(username,message);
            
            request.setAttribute("username", username);
            RequestDispatcher view = request.getRequestDispatcher("/index.jsp");  
            view.forward(request, response);
        }
        
        private void insert_user_message_in_db(String username, String message) {
    
            try{
                Class.forName("com.mysql.cj.jdbc.Driver");
                Connection conn = DriverManager.getConnection("jdbc:mysql://localhost:3306/messages?useSSL=false", "root", "password");
                
                String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";
    
                PreparedStatement statement = conn.prepareStatement(sql);
                statement.setString(1, username);
                statement.setString(2, message);
                int result = statement.executeUpdate();
            } catch(Exception e){
                System.out.println(e);
            }
        }
    }