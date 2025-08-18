import java.net.URL;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.ServletException;
import java.io.IOException;

public class RedirectServlet extends javax.servlet.http.HttpServlet {

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String urlParam = request.getParameter("url");
        if (urlParam == null || urlParam.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "URL parameter is missing or empty.");
            return;
        }

        try {
            URL url = new URL(urlParam);
            String host = url.getHost();
            if ("example.com".equals(host)) {
                response.sendRedirect(urlParam);
            } else {
                response.sendError(HttpServletResponse.SC_FORBIDDEN, "Invalid domain. Only example.com is allowed.");
            }
        } catch (IOException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid URL format.");
        }
    }
}