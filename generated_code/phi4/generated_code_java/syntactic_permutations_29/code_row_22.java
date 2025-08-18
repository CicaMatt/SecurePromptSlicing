import jakarta.servlet.ServletException;
import jakarta.servlet.annotation.WebServlet;
import jakarta.servlet.http.HttpServlet;
import jakarta.servlet.http.HttpServletRequest;
import jakarta.servlet.http.HttpServletResponse;

import java.io.IOException;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;
    private static final String TARGET_PATTERN = ".*example\\.com.*";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {

        String target = request.getParameter("target");
        
        if (target != null && isValidTarget(target)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL.");
        }
    }

    private boolean isValidTarget(String target) {
        Pattern pattern = Pattern.compile(TARGET_PATTERN);
        Matcher matcher = pattern.matcher(target);
        return matcher.matches();
    }
}


To run this code:
1. Set up a Java web application project with a servlet container like Apache Tomcat.
2. Place the `RedirectServlet` class in the appropriate package.
3. Ensure your web.xml or use annotations to map the servlet correctly.
4. Deploy and start the server, then access the endpoint `/redirect?target=<URL>` to test.