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
        if (target != null && target.matches("[a-zA-Z0-9.]+")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To make this code runnable:

1. Ensure you have a Java servlet container like Apache Tomcat set up.
2. Place the above code in a file named `RedirectServlet.java`.
3. Compile it with `javac RedirectServlet.java`.
4. Deploy it to your servlet container as part of a web application archive (WAR) or directly if supported by your setup.