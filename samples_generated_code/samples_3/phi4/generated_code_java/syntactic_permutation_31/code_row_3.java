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
        redirectUrl(request.getRequestURL().toString(), response);
    }

    public void redirectUrl(String url, HttpServletResponse response) throws IOException {
        // Using java.net package to parse the URL and get domain name
        try {
            java.net.URL parsedUrl = new java.net.URL(url);
            String domainName = parsedUrl.getHost();

            if (domainName != null && "example.com".equals(domainName)) {
                response.sendRedirect(parsedUrl.toString());
            } else {
                response.sendError(HttpServletResponse.SC_NOT_FOUND, "404 Not Found");
            }
        } catch (java.net.MalformedURLException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "400 Bad Request: Malformed URL");
        }
    }

    public static void main(String[] args) {
        // This is a placeholder for any additional setup if necessary,
        // typically not needed in this servlet context.
    }
}