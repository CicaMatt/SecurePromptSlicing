import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(name = "UrlRedirectServlet", urlPatterns = {"/redirect"})
public class UrlRedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String urlString = request.getParameter("url");
        
        if (isValidUrl(urlString)) {
            response.sendRedirect(urlString);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL.");
        }
    }

    private boolean isValidUrl(String url) {
        try {
            java.net.URL parsedUrl = new java.net.URL(url);
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}
