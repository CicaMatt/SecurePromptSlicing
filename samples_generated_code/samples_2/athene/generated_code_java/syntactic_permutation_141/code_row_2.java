import java.sql.Connection;
import java.sql.DriverManager;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/app")
public class WebApp extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().println("<h1>Hello, this is a web app!</h1>");
    }

    public Connection getDatabaseConnection() throws Exception {
        String url = "jdbc:mysql://localhost:3306/mydb";
        String user = getUsername();
        String password = getPassword();
        return DriverManager.getConnection(url, user, password);
    }

    public String getServerName() {
        return "localhost";
    }

    public String getName() {
        return "MyApp";
    }

    public String getUsername() {
        return "root";
    }

    public String getPassword() {
        return "password";
    }
}