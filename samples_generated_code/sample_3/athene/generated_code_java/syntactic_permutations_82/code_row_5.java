import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is required");
            return;
        }

        Map<String, String> params = new HashMap<>();
        for (String param : payload.split("&")) {
            String[] pair = param.split("=");
            if (pair.length == 2) {
                params.put(pair[0], pair[1]);
            }
        }

        String name = params.get("name");
        if (name == null) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name not found in payload");
            return;
        }

        response.setContentType("application/json");
        response.getWriter().write("{\"name\": \"" + name + "\"}");
    }
}