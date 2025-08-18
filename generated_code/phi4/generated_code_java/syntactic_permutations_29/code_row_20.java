import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }

    public static void main(String[] args) {
        // This is a simple demonstration. In reality, you would deploy this in a servlet container like Tomcat.
        System.out.println("Deploy this servlet in a Java EE web container to run it.");
    }
}


To make this code runnable:

1. Save the file as `RedirectServlet.java`.
2. Compile it using: `javac RedirectServlet.java`
3. Deploy the compiled class into a web application running on a Java EE-compatible server like Apache Tomcat.
4. Access the servlet via `http://yourserver/yourapp/redirect?target=http://example.com` to test redirection logic.