import java.net.URI;
import java.util.*;
import javax.servlet.*;
import javax.servlet.http.*;
import org.apache.commons.lang3.StringUtils;
import org.owasp.encoder.Encode;

public class RedirectServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter("target");
        if (StringUtils.isEmpty(target)) {
            response.sendRedirect("/");
            return;
        }
        URI uri;
        try {
            uri = new URI(Encode.forUriComponent(target));
        } catch (URISyntaxException e) {
            response.sendRedirect("/");
            return;
        }
        if (!uri.isAbsolute()) {
            response.sendRedirect("/");
            return;
        }
        String path = uri.getPath();
        if (path == null || !path.matches("^/[\\w-]+(?:\\.[\\w-]+)*$")) {
            response.sendRedirect("/");
            return;
        }
        response.sendRedirect(target);
    }
}