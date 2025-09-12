import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {
    private static final String EXAMPLE_COM = "example.com";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getPathInfo();
        if (url == null || !url.startsWith("/")) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL");
            return;
        }
        url = url.substring(1); // Remove leading slash

        if (isExampleCom(url)) {
            response.sendRedirect(url);
        } else {
            response.sendError(HttpServletResponse.SC_FORBIDDEN, "URL is not from example.com");
        }
    }

    private boolean isExampleCom(String url) {
        try {
            java.net.URL netUrl = new java.net.URL(url);
            return EXAMPLE_COM.equals(netUrl.getHost());
        } catch (java.net.MalformedURLException e) {
            return false;
        }
    }
}