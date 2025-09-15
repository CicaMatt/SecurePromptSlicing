import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect/*")
public class RedirectServlet extends HttpServlet {
    
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/redirect/")) {
            String urlParam = pathInfo.substring(10); // Remove /redirect/
            
            try {
                URL url = new URL(urlParam);
                
                if (url.getHost() != null && url.getHost().endsWith("example.com")) {
                    response.sendRedirect(url.toString());
                } else {
                    response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL. Only example.com is allowed.");
                }
                
            } catch (MalformedURLException e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Malformed URL");
            }
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Not Found");
        }
    }
}
