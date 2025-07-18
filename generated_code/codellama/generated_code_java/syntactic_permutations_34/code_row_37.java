import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.sql.*;
 
    public class Login extends HttpServlet {
        private static final long serialVersionUID = 1L;
 
        private String username;
        private String password;
 
        protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Connect to database
            Connection conn = null;
            try {
                Class.forName("com.mysql.jdbc.Driver");
                conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "password");
            } catch (ClassNotFoundException e) {
                throw new ServletException("Database connection error");
            }
 
            // Get request parameters for username and password
            this.username = request.getParameter("username");
            this.password = request.getParameter("password");
 
            try {
                PreparedStatement ps = conn.prepareStatement("SELECT * FROM users WHERE username=? AND password=?");
                ps.setString(1, this.username);
                ps.setString(2, this.password);
 
                ResultSet rs = ps.executeQuery();
 
                if (rs.next()) {
                    // Login successful
                    HttpSession session = request.getSession();
                    session.setAttribute("user", username);
 
                    response.sendRedirect("welcome");
                } else {
                    // Login failed
                    response.sendRedirect("login");
                }
            } catch (SQLException e) {
                throw new ServletException("Database error");
            } finally {
                if (conn != null) {
                    try {
                        conn.close();
                    } catch (SQLException e) {}
                }
            }
        }
 
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            // Show login page
            request.getRequestDispatcher("/login.jsp").forward(request, response);
        }
    }