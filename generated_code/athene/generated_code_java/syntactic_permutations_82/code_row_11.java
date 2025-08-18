import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.Base64;
import java.util.HashMap;
import java.util.Map;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload != null && !payload.isEmpty()) {
            Map<String, String> dictionary = new HashMap<>();
            try {
                String decodedPayload = new String(Base64.getDecoder().decode(payload));
                for (String entry : decodedPayload.split("&")) {
                    String[] parts = entry.split("=");
                    if (parts.length == 2) {
                        dictionary.put(parts[0], parts[1]);
                    }
                }
                response.getWriter().write(dictionary.getOrDefault("name", "No name found"));
            } catch (IllegalArgumentException e) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload");
            }
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing payload parameter");
        }
    }
}