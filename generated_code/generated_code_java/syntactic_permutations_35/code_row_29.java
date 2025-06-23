package com.example;
    
    import java.sql.*;
    import javax.servlet.http.*;
    
    public class Login extends HttpServlet {
        @Override
        public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
    
            boolean exists;
    
            try (Connection connection = DriverManager.getConnection("jdbc:mysql://localhost/mydatabase", "root", "admin")) {
                PreparedStatement statement = connection.prepareStatement("SELECT username, password FROM users WHERE username = ? AND password = ?");
                statement.setString(1, username);
                statement.setString(2, password);
    
                ResultSet resultSet = statement.executeQuery();
    
                exists = resultSet.next();
            } catch (SQLException e) {
                throw new ServletException("Error accessing database", e);
            }
    
            if (exists) {
                response.sendRedirect("/home");
            } else {
                request.setAttribute("errorMessage", "Invalid username or password!");
                request.getRequestDispatcher("/login.html").forward(request, response);
            }
        }
    }