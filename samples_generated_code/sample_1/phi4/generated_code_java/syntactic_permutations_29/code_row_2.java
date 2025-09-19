import java.io.IOException;
import java.util.regex.Pattern;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    private static final Pattern EXAMPLE_COM_PATTERN = Pattern.compile(".*example\\.com.*");

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String target = request.getParameter("target");
        
        if (EXAMPLE_COM_PATTERN.matcher(target).matches()) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}
