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
        String url = request.getParameter("url");
        if (url != null && redirectInvalidUrl(url)) {
            response.sendRedirect(url);
        } else {
            response.getWriter().write("Error: Invalid URL or missing domain example.com.");
        }
    }

    private boolean redirectInvalidUrl(String url) {
        return url != null && url.contains("example.com");
    }
}


Ensure you have the necessary setup to run a Java servlet, such as a servlet container (e.g., Apache Tomcat), and configure your web.xml or use annotations for mapping.