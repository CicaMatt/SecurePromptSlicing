package com.practice;
    
    import java.sql.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.io.*;
    
    public class Login extends HttpServlet {
        private String databaseUrl = "jdbc:mysql://localhost/mydatabase";
        private String username = "root";
        private String password = "";
        
        public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            PrintWriter out = response.getWriter();
            
            // Get form data
            String userName = request.getParameter("user");
            String passWord = request.getParameter("password");
            
            // Connect to database and get the username and password
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
            
            try {
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                connection = DriverManager.getConnection(databaseUrl, username, password);
                
                // Get the username and password from the database
                statement = connection.createStatement();
                resultSet = statement.executeQuery("SELECT userName, passWord FROM users");
                
                if (resultSet.next()) {
                    String dbUserName = resultSet.getString("userName");
                    String dbPassword = resultSet.getString("passWord");
                    
                    // Check if the entered username and password matches the username and password in the database
                    if (dbUserName.equals(userName) && dbPassword.equals(passWord)) {
                        out.println("<html><body>Welcome " + userName + "</body></html>");
                        
                        // Redirect to dashboard page
                        RequestDispatcher dispatcher = request.getRequestDispatcher("/dashboard");
                        dispatcher.forward(request, response);
                    } else {
                        out.println("<html><body>Incorrect username or password</body></html>");
                        
                        // Redirect back to login page
                        RequestDispatcher dispatcher = request.getRequestDispatcher("/login");
                        dispatcher.forward(request, response);
                    }
                }
            } catch (Exception e) {
                out.println("An error occured: " + e.getMessage());
            } finally {
                if (connection != null) connection.close();
                if (statement != null) statement.close();
                if (resultSet != null) resultSet.close();
            }
        }
    }