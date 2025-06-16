import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.util.*;
    import java.sql.*;

    public class Login extends HttpServlet {
        private String dbUrl = "jdbc:postgresql://localhost/mydb";
        private String userName = "testUser";
        private String password = "testPass";
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            Connection connection = null;
            Statement statement = null;
            ResultSet resultSet = null;
    
            try {
                String username = request.getParameter("username");
                String password = request.getParameter("password");
    
                Class.forName("org.postgresql.Driver");
                connection = DriverManager.getConnection(dbUrl, userName, password);
    
                statement = connection.createStatement();
    
                resultSet = statement.executeQuery("SELECT * FROM users WHERE username = '" + username + "' AND password = '" + password + "'");
    
                if (resultSet.next()) {
                    response.sendRedirect("success");
                } else {
                    response.sendRedirect("cant_login");
                }
            } catch(Exception e) {
                response.sendRedirect("internal_server_error");
            } finally {
                if (resultSet != null) {
                    try {
                        resultSet.close();
                    } catch(SQLException e) {}
                }
    
                if (statement != null) {
                    try {
                        statement.close();
                    } catch(SQLException e) {}
                }
    
                if (connection != null) {
                    try {
                        connection.close();
                    } catch(SQLException e) {}
                }
            }
        }
    }