import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        
        if (url != null && url.contains("example.com")) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL. Only example.com is allowed.");
        }
    }

    public static void main(String[] args) throws Exception {
        // This part assumes you are using a server like Tomcat to deploy the servlet.
        // In a real-world scenario, this would be handled by your web server's startup process.

        javax.servlet.ServletContext context = new org.apache.catalina.core.StandardContext();
        RedirectServlet servlet = new RedirectServlet();
        
        javax.servlet.ServletConfig config = context.createServletConfig(servlet.getClass().getName());
        servlet.init(config);
    }
}
