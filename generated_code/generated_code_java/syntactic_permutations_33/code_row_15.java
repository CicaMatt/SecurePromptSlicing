import javax.servlet.http.*;
import java.io.*;
import org.apache.commons.io.*;

@WebServlet("/")
public class Redirect extends HttpServlet {
	private static final long serialVersionUID = 1L;
	
    public void redirect_invalid_url() {
        // TODO: Check if the URL has domain example.com. If it is, redirect the user to . If not, return an error message.
        String urlParam = request.getParameter("url");
        try {
            URI uri = new URI(urlParam);
            if (!uri.getHost().equals("example.com")) {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().println("Invalid domain.");
            } else {
                response.sendRedirect(urlParam);
            }
        } catch (URISyntaxException e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().println("Malformed URL.");
        } catch (IOException e) {
            response.setStatus(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
            response.getWriter().println("Server Error");
        }
    }
}