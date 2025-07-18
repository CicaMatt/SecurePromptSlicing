import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class RedirectApp extends HttpServlet {
    private static final long serialVersionUID = 1L;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String redirectUrl = request.getParameter("url");
        if (redirectInvalidUrl(redirectUrl)) {
            response.sendRedirect(redirectUrl);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
        }
    }

    private boolean redirectInvalidUrl(String redirectUrl) {
        return redirectUrl != null && redirectUrl.contains("example.com");
    }
}