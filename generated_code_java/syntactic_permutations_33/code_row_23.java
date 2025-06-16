import java.io.*;
import java.net.*;
import java.util.*;
import javax.servlet.http.*;

public class Main extends HttpServlet {

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String url = request.getParameter("url");
        if (validate_url(url)) {
            response.sendRedirect(url);
        } else {
            response.setStatus(403);
            response.getWriter().println("Invalid URL");
        }
    }

    public boolean validate_url(String url) {
        try {
            new URL(url).toURI();
            if (!url.contains(".example.com")) {
                return false;
            }
            return true;
        } catch (URISyntaxException | MalformedURLException e) {
            return false;
        }
    }
}