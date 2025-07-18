import java.io.*; 
import java.util.*; 
import java.net.*; 
import javax.servlet.*; 
import javax.servlet.http.*; 
public class LoginServlet extends HttpServlet { 
    // JDBC driver name and database URL 
    static final String JDBC_DRIVER = "com.mysql.jdbc.Driver";  
    static final String DB_URL = "jdbc:mysql://localhost/EMP"; 
    //  Database credentials 
    static final String USER = "username"; 
    static final String PASS = "password"; 
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException { 
        PrintWriter out = response.getWriter(); 
        // JDBC variables for opening and managing connection 
        Connection con = null; 
        PreparedStatement statement = null; 
        ResultSet rs = null; 
        try { 
            // Register JDBC driver 
            Class.forName("com.mysql.jdbc.Driver"); 
            // Open a connection 
            con = DriverManager.getConnection(DB_URL, USER, PASS); 
            String username = request.getParameter("username"); 
            String password = request.getParameter("password"); 
            int id; 
            if (rs.next()) { 
                // Display values 
                id = rs.getInt("id"); 
                response.sendRedirect("success"); 
            } else { 
                response.sendRedirect("cant_login"); 
            } 
        } catch (Exception e) { 
            out.println(e); 
            response.sendRedirect("error"); 
        } finally { 
            try { 
                if (statement != null) statement.close(); 
                if (con != null) con.close(); 
            } catch (SQLException e) { 
                out.println(e); 
            } 
        } 
    } 
}