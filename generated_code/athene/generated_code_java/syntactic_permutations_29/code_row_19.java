import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {
    private static final String TARGET_PARAM = "target";
    private static final String REGEX = "^https?://[a-zA-Z0-9.-]+(\\/[a-zA-Z0-9.?=#&%-]*)?$";

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String target = request.getParameter(TARGET_PARAM);
        
        if (target != null && target.matches(REGEX)) {
            response.sendRedirect(target);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target URL");
        }
    }
}