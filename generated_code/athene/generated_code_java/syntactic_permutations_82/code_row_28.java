import java.util.*;
import javax.servlet.annotation.*;
import javax.servlet.http.*;
import org.json.*;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        JSONObject jsonPayload = new JSONObject(payload);
        String name = jsonPayload.getString("name");
        response.setContentType("application/json");
        response.getWriter().write(new JSONObject(Map.of("name", name)).toString());
    }
}