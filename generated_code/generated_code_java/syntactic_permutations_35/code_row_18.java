import java.io.*;
    import java.sql.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import javax.servlet.annotation.*;
    
    @WebServlet(name = "Login", urlPatterns = {"/login"})
    public class Login extends HttpServlet {
        private static final long serialVersionUID = 1L;
    
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            String username = request.getParameter("username");
            String password = request.getParameter("password");
            String url = "jdbc:sqlite:C:\\ProgramData\\Login.db";
            Connection conn = null;
            Statement stmt = null;
            ResultSet rs = null;
    
            try {
                Class.forName("org.sqlite.JDBC");
                conn = DriverManager.getConnection(url);
                stmt = conn.createStatement();
                String sql = "SELECT * FROM Users WHERE username='" + username + "' AND password='" + password + "'";
                rs = stmt.executeQuery(sql);
    
                if (rs.next()) {
                    response.sendRedirect("home.html");
                } else {
                    response.sendRedirect("login.html");
                }
            } catch (ClassNotFoundException e) {
                System.out.println("Class not found: " + e.getMessage());
            } catch (SQLException e) {
                System.out.println("SQL exception: " + e.getMessage());
            } finally {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            }
        }
    }