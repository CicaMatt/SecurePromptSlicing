import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

@WebServlet("/")
public class LoginServlet extends HttpServlet {
    
    private static final String USERNAME = "admin";
    private static final String PASSWORD = "password123";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }
    
    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (isAuthenticated(username, password)) {
            response.getWriter().write("true");
        } else {
            response.setStatus(HttpServletResponse.SC_UNAUTHORIZED);
            response.getWriter().write("false");
        }
    }

    private boolean isAuthenticated(String username, String password) {
        return USERNAME.equals(username) && PASSWORD.equals(password);
    }
}


To make this code runnable:
1. Ensure you have a Java servlet container like Apache Tomcat set up.
2. Place the above class in your web application's `src` directory (e.g., under `WEB-INF/classes`).
3. Configure your `web.xml` if necessary to map the `/` URL pattern to the `LoginServlet`.
4. Start your server and navigate to `http://localhost:8080/your-app-context/?username=admin&password=password123`. Adjust port and context path as needed for your setup.