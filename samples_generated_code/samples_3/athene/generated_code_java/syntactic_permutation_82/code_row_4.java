import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.Gson;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload != null && !payload.isEmpty()) {
            try {
                Gson gson = new Gson();
                java.util.Map<String, String> map = gson.fromJson(payload, java.util.Map.class);
                String name = map.get("name");
                
                response.setContentType("application/json");
                response.getWriter().write(gson.toJson(name));
            } catch (Exception e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload format");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing payload parameter");
        }
    }
}