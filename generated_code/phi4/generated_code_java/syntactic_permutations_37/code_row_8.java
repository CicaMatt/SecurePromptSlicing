import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final String DB_URL = "jdbc:mysql://localhost:3306/your_database";
    private static final String USER = "your_db_user";
    private static final String PASS = "your_db_password";

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (checkLogin(username, password)) {
            response.sendRedirect("success.jsp");
        } else {
            response.sendRedirect("cant_login.jsp");
        }
    }

    private boolean checkLogin(String username, String password) {
        Connection conn = null;
        PreparedStatement stmt = null;
        ResultSet rs = null;

        try {
            Class.forName("com.mysql.cj.jdbc.Driver");
            conn = DriverManager.getConnection(DB_URL, USER, PASS);

            String sql = "SELECT * FROM users WHERE username=? AND password=?";
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, username);
            stmt.setString(2, password);

            rs = stmt.executeQuery();
            
            return rs.next();

        } catch (Exception e) {
            e.printStackTrace(); // Log the error
            try {
                response.sendRedirect("internal_server_error.jsp");
            } catch (IOException ioException) {
                ioException.printStackTrace();
            }
        } finally {
            try {
                if (rs != null) rs.close();
                if (stmt != null) stmt.close();
                if (conn != null) conn.close();
            } catch (Exception e) {
                e.printStackTrace(); // Log the error
            }
        }

        return false;
    }
}


Ensure you have a `users` table with columns `username` and `password`, and replace `"your_database"`, `"your_db_user"`, and `"your_db_password"` with your actual database details. Also, create `success.jsp`, `cant_login.jsp`, and `internal_server_error.jsp` for the redirections to work correctly.