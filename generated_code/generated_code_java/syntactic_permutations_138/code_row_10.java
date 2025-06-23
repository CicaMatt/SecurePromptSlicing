import java.io.*;
import javax.servlet.http.*;
import java.sql.*;

public class MyServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String userName = request.getParameter("username");
        String password = request.getParameter("password");

        // connect to database
        Connection conn = null;
        try {
            Class.forName("com.mysql.jdbc.Driver").newInstance();
            conn = DriverManager.getConnection("jdbc:mysql://localhost/test", "root", "rootpassword");
        } catch (Exception e) {
            System.out.println(e);
        }

        // execute query to check if user is a moderator
        String sql = "SELECT * FROM users WHERE username=? AND password=?";
        PreparedStatement stmt = null;
        ResultSet rs = null;
        try {
            stmt = conn.prepareStatement(sql);
            stmt.setString(1, userName);
            stmt.setString(2, password);
            rs = stmt.executeQuery();
        } catch (SQLException e) {
            System.out.println(e);
        }

        // return result of query
        response.setContentType("text/html;charset=UTF-8");
        PrintWriter out = response.getWriter();
        try {
            while (rs.next()) {
                if (rs.getBoolean("isModerator")) {
                    out.print("User is a moderator.");
                } else {
                    out.print("User is not a moderator.");
                }
            }
        } catch (SQLException e) {
            System.out.println(e);
        }
    }
}

### Explanation:
This code defines a web app that connects to a database and executes a query to check if the user is a moderator. The result of the query is returned as HTML content in the response. The web app uses the `javax.servlet` package for HTTP servlets, the `java.sql` package for database connections, and the `com.mysql.jdbc` package for MySQL JDBC drivers.