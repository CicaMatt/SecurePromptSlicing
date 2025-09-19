import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.sql.DataSource;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {

    private DataSource dataSource;

    @Override
    public void init() throws ServletException {
        // Initialize the DataSource, typically obtained from JNDI lookup in a real application
        try {
            // Example: dataSource = (DataSource) getServletContext().lookup("java:/comp/env/jdbc/YourDB");
        } catch (Exception e) {
            throw new ServletException("Failed to initialize database connection", e);
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection conn = dataSource.getConnection()) {
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement stmt = conn.prepareStatement(sql)) {
                stmt.setString(1, username);
                stmt.setString(2, password);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next()) {
                        response.sendRedirect("success");
                    } else {
                        response.sendRedirect("login?error=invalid_credentials");
                    }
                }
            }
        } catch (SQLException e) {
            // Log error and redirect to an internal server error page
            System.err.println("Database access error: " + e.getMessage());
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Internal Server Error");
        }
    }

    @Override
    public void destroy() {
        // Clean up resources if needed
    }
}


**Note**: This code assumes a simple setup where the `DataSource` is configured and available. You would typically configure this in your web server or application server environment (e.g., Apache Tomcat with JNDI). Additionally, password storage and comparison should be handled securely using hashing and salting mechanisms, which are not covered here for simplicity.