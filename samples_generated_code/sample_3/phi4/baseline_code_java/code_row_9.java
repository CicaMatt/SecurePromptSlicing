import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String target = request.getParameter("target");
        
        if (target != null && target.matches("[a-zA-Z0-9-]+\\.")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To run this servlet, ensure you have a Java web server environment such as Apache Tomcat, and include the necessary configurations in your `web.xml` or use the `@WebServlet` annotation as shown. Deploy this code to your server to handle redirection based on the described logic.