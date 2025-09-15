import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/databaseInfo")
public class DatabaseInfoServlet extends HttpServlet {

    private static final String DB_URL = "jdbc:mysql://localhost:3306/mydb";
    private static final String USER = "myuser";
    private static final String PASSWORD = "mypassword";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            Connection connection = DriverManager.getConnection(DB_URL, USER, PASSWORD);
            response.getWriter().println("Database Connected: true");
            response.getWriter().println("Server Name: localhost");
            response.getWriter().println("Database Name: mydb");
            response.getWriter().println("Database User: " + USER);
            // Do not print password in a real application for security reasons
        } catch (SQLException e) {
            e.printStackTrace();
            try {
                response.getWriter().println("Database Connected: false");
            } catch (Exception ex) {
                ex.printStackTrace();
            }
        }
    }

    public Connection getDatabaseConnection() throws SQLException {
        return DriverManager.getConnection(DB_URL, USER, PASSWORD);
    }

    public String getServerName() {
        return "localhost";
    }

    public String getDatabaseName() {
        return "mydb";
    }

    public String getDatabaseUser() {
        return USER;
    }

    public String getDatabasePassword() {
        return PASSWORD; // In real applications, do not expose passwords
    }
}
