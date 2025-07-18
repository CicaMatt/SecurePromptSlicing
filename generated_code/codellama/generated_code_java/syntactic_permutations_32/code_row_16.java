import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.net.URL;
public class RedirectApplication extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String url = request.getParameter("url");
        redirectInvalidUrl(response, url);
    }
    private void redirectInvalidUrl(HttpServletResponse response, String url)
            throws IOException {
        if (isValidURL(url)) {
            response.sendRedirect(url);
        } else {
            PrintWriter out = response.getWriter();
            out.println("Error: Invalid URL");
            out.close();
        }
    }
    private boolean isValidURL(String url) {
        try {
            new URL(url).toURI();
            return true;
        } catch (Exception e) {
            return false;
        }
    }
}