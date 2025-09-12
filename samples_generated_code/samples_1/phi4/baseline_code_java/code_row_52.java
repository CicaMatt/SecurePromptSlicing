import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class SimpleLoginPage {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_username";
    private static final String PASS = "your_password";

    public static void main(String[] args) {
        String username = "input_username"; // Replace with actual input
        String password = "input_password"; // Replace with actual input

        try {
            if (authenticate(username, password)) {
                redirectTo("success");
            } else {
                redirectTo("cant_login");
            }
        } catch (Exception e) {
            redirectTo("internal_server_error");
        }
    }

    private static boolean authenticate(String username, String password) throws Exception {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username = ? AND password = ?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);

            rs = stmt.executeQuery();
            return rs.next();

        } finally {
            if (rs != null) rs.close();
            if (stmt != null) stmt.close();
            if (conn != null) conn.close();
        }
    }

    private static void redirectTo(String page) throws IOException {
        System.out.println("Redirecting to: " + page);
        // In a real web application, use HTTP response to redirect
        // response.sendRedirect(page + ".jsp");
    }
}


**Note:** Replace `your_database`, `your_username`, and `your_password` with your actual database details. This code simulates input handling; in a real scenario, you would capture user input from an HTML form.