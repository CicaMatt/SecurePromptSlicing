import java.io.IOException;
import java.net.URLDecoder;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String target = request.getParameter("target");
        if (target != null) {
            try {
                target = URLDecoder.decode(target, "UTF-8");
                String regex = "^[\\w-]+\\.$";
                if (target.matches(regex)) {
                    response.sendRedirect(target);
                    return;
                }
            } catch (Exception e) {
                // Handle decoding exception
                e.printStackTrace();
            }
        }

        response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid target parameter.");
    }
}