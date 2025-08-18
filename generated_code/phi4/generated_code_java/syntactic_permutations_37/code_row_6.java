import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.io.IOException;

public class LoginServlet extends javax.servlet.http.HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/yourDatabaseName";
    private static final String USER = "yourUsername";
    private static final String PASS = "yourPassword";

    protected void doPost(javax.servlet.http.HttpServletRequest request, 
                          javax.servlet.http.HttpServletResponse response) 
            throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        try (Connection conn = DriverManager.getConnection(DB_URL, USER, PASS)) {
            String query = "SELECT COUNT(*) FROM users WHERE username = ? AND password = ?";
            try (PreparedStatement stmt = conn.prepareStatement(query)) {
                stmt.setString(1, username);
                stmt.setString(2, password);

                try (ResultSet rs = stmt.executeQuery()) {
                    if (rs.next() && rs.getInt(1) > 0) {
                        response.sendRedirect("success");
                    } else {
                        response.sendRedirect("cant_login");
                    }
                }
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Internal Server Error");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in an actual server environment
    }
}


Make sure to replace `yourDatabaseName`, `yourUsername`, and `yourPassword` with your actual database details. Also, ensure that you have the necessary MySQL connector library included in your project's classpath.