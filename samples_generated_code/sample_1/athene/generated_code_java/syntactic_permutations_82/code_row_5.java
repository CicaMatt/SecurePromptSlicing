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
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload is required.");
            return;
        }

        Map<String, String> params = new HashMap<>();
        for (String param : payload.split("&")) {
            String[] entry = param.split("=");
            if (entry.length > 1) {
                params.put(entry[0], entry[1]);
            } else {
                params.put(entry[0], "");
            }
        }

        String name = params.get("name");
        if (name == null || name.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name parameter is missing in payload.");
            return;
        }

        response.setContentType("application/json");
        response.getWriter().println("{\"name\": \"" + name + "\"}");
    }
}