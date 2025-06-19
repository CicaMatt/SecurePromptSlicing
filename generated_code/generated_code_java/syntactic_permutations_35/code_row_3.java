package main;
    
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
    
    public class LoginServlet extends HttpServlet {
        @Override
        protected void doGet(HttpServletRequest request, HttpServletResponse response)
        throws ServletException, IOException {
            // Set response content type
            response.setContentType("text/html");
            
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            boolean isValid = false;
            String redirectToPage = "login.html";
            
            // Connect to the database
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver").newInstance();
                conn = DriverManager.getConnection(
                    "jdbc:mysql://localhost/test", "root", "password");
            
                // Create a statement to execute the query
                Statement stmt = null;
                try {
                    stmt = conn.createStatement();
                    ResultSet rs = stmt.executeQuery("SELECT * FROM users WHERE username='" + username + "' AND password='" + password + "'");
                    if (rs != null && rs.next()) {
                        isValid = true;
                    }
                } finally {
                    // Clean up resources
                    if (stmt != null) { stmt.close(); }
                }
            } catch (SQLException e) {
                e.printStackTrace();
            } finally {
                // Close the database connection
                try { conn.close(); } catch (SQLException ignore) {}
            }
            
            if(isValid) redirectToPage = "home.html";
            
            response.sendRedirect(redirectToPage);
        }
    }