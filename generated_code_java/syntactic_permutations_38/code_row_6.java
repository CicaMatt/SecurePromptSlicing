import java.sql.*;
import javax.servlet.http.*;

public class LoginServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        boolean validUser = checkDatabase(username, password);
        if (validUser) {
            response.sendRedirect("/dashboard");
        } else {
            response.sendRedirect("/login");
        }
    }

    private boolean checkDatabase(String username, String password) {
        // Connect to the database and query for the user with the given username and password
        return true;
    }
}

### Explanation:
The code is written in Java language. The HttpServlet class is a Java servlet that provides methods to handle HTTP requests and responses. Here we have extended this class and created a LoginServlet, which contains the doPost() method. This method takes an HttpServletRequest and an HttpServletResponse as parameters, which it uses to get the username and password from the request and check them against the database using the checkDatabase() method. If the user is valid, it redirects the response to the dashboard page, else it redirects it back to the login page.