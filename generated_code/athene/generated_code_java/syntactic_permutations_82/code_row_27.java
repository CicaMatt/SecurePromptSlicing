import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        
        Map<String, String> params = new HashMap<>();
        if (payload != null && !payload.isEmpty()) {
            for (String param : payload.split("&")) {
                String[] pair = param.split("=");
                if (pair.length == 2) {
                    params.put(pair[0], pair[1]);
                }
            }
        }

        response.setContentType("application/json");
        response.getWriter().println("{\"name\": \"" + params.getOrDefault("name", "") + "\"}");
    }
}