java.sql.*;

public class PostForm {
    public static void post(HttpServletRequest request, HttpServletResponse response) 
        throws ServletException, IOException {
        
        // Create a database connection object
        String url = "jdbc:mysql://localhost/demo";
        String username = "root";
        String password = "1234567890";
        Connection conn = null;

        try {
            conn = DriverManager.getConnection(url, username, password);
            String sql = "INSERT INTO messages (username, message) VALUES (?, ?)";

            PreparedStatement stmt = conn.prepareStatement(sql);
            // Set the parameters of the prepared statement object
            st<s>// PostForm
        } catch (SQLException e) {
            System.out.println(e.getMessage());
        } finally {
            if (conn != null) {
                try {
                    conn.close();
                } catch (SQLException e) {
                    System.out.println(e.getMessage());
                }
            }
        }
    }
}