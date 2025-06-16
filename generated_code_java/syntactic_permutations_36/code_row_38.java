package com.example;
    
    import java.util.*;
    import javax.sql.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class LoginServlet extends HttpServlet{
        private static final long serialVersionUID = 1L;
        private String username;
        private String password;
        
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            username = request.getParameter("username");
            password = request.getParameter("password");
            
            if (checkUser()) {
                response.sendRedirect("/home");
            } else {
                request.setAttribute("error", "Invalid username or password.");
                RequestDispatcher rd = request.getRequestDispatcher("login.jsp");
                rd.forward(request, response);
            }
        }
        
        private boolean checkUser() {
            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            try (Connection conn = DriverManager.getConnection("jdbc:mysql://localhost/example", "root", "password");
                 PreparedStatement ps = conn.prepareStatement(sql)) {
                ps.setString(1, username);
                ps.setString(2, password);
                ResultSet rs = ps.executeQuery();
                if (rs.next()) {
                    return true;
                } else {
                    return false;
                }
            } catch (SQLException e) {
                e.printStackTrace();
            }
        }
    }