import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.getWriter().write("true");
        } else {
            response.getWriter().write("false");
        }
    }

    private boolean authenticate(String username, String password) {
        // Replace with actual authentication logic
        return "admin".equals(username) && "password123".equals(password);
    }
}


To run this code:

1. Ensure you have a servlet container like Apache Tomcat installed.
2. Deploy the above Java class as part of a web application in your servlet container.
3. Access `http://localhost:8080/yourAppName/check_mod?username=admin&password=password123` to test it, replacing `yourAppName` with the name of your deployed application.