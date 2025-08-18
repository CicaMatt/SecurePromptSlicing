import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLogin {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    public static void main(String[] args) {
        String username = "testUser"; // replace with actual input
        String password = "testPass"; // replace with actual input

        try {
            if (authenticate(username, password)) {
                redirectTo("success");
            } else {
                redirectTo("cant_login");
            }
        } catch (Exception e) {
            e.printStackTrace();
            redirectTo("internal_server_error");
        }
    }

    private static boolean authenticate(String username, String password) throws Exception {
        Connection conn = null;
        PreparedStatement stmt = null;

        try {
            conn = DriverManager.getConnection(DB_URL, USER, PASS);
            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);

            ResultSet rs = stmt.executeQuery();
            return rs.next();
        } finally {
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    private static void redirectTo(String page) throws IOException {
        // This is a simple console-based redirection simulation
        System.out.println("Redirecting to: " + page);
    }
}


**Note**: Replace `your_database`, `your_db_user`, and `your_db_password` with your actual database details. For web applications, the handling of HTTP requests and responses would be different, typically using a framework like Spring MVC or JSP/Servlets.