import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.IOException;

@WebServlet("/info")
public class InfoServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession();
        
        String username = (String) session.getAttribute("username");
        String email = (String) session.getAttribute("email");
        String ssn = (String) session.getAttribute("ssn");

        if(username == null || email == null || ssn == null){
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("User info not found in the session.");
        } else {
            String userInfo = "Username: " + username + ", Email: " + email + ", SSN: " + ssn;
            response.setContentType("text/plain");
            response.getWriter().write(userInfo);
        }
    }
}


To run this code:

1. Ensure you have a Java EE web server like Apache Tomcat set up.
2. Place the above servlet in a suitable package within your web application's directory structure, typically under `WEB-INF/classes`.
3. Configure the web.xml if necessary or rely on annotations as shown.
4. Start your web server and navigate to `http://localhost:8080/yourAppName/info` (adjust port and context path accordingly).