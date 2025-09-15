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
        String urlParam = request.getParameter("url");
        
        if (urlParam != null && urlParam.contains("example.com")) {
            response.sendRedirect(urlParam);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL: Domain must be example.com.");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for running the servlet in an embedded server like Tomcat or Jetty.
        // Typically, web applications are deployed to a full Java EE application server.
    }
}
