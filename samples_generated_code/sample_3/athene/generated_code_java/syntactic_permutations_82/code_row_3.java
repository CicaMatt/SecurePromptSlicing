import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class PayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is required");
            return;
        }

        Map<String, String> params = new HashMap<>();
        String[] entries = payload.split("&");
        for (String entry : entries) {
            String[] keyValue = entry.split("=", 2);
            if (keyValue.length == 2) {
                params.put(keyValue[0], URLDecoder.decode(keyValue[1], "UTF-8"));
            }
        }

        response.setContentType("text/plain");
        response.getWriter().println(params.getOrDefault("name", "Name not found"));
    }
}