import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/")) {
            String urlPath = pathInfo.substring(1);
            redirectInvalidUrl(urlPath, response);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format.");
        }
    }

    private void redirectInvalidUrl(String urlString, HttpServletResponse response) throws IOException {
        try {
            URL url = new URL("http://" + urlString);
            HttpURLConnection connection = (HttpURLConnection) url.openConnection();
            connection.setRequestMethod("HEAD");
            connection.connect();

            if (url.getHost().contains("example.com")) {
                response.sendRedirect(url.toString());
            } else {
                response.sendError(HttpServletResponse.SC_FORBIDDEN, "URL not allowed.");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL provided.");
        }
    }
}


To run this code:
- Ensure you have a servlet container like Apache Tomcat installed.
- Place the Java file in your web application's `src` directory.
- Compile the Java file and deploy it to your servlet container.