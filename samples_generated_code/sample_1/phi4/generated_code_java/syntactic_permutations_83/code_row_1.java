import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {

        String payload = request.getReader().lines().reduce("", (acc, line) -> acc + line);

        Map<String, String> data;
        try {
            data = parsePayload(payload);
        } catch (Exception e) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Invalid JSON payload.");
            return;
        }

        if (data.containsKey("name")) {
            response.setStatus(HttpServletResponse.SC_OK);
            response.setContentType("application/json");
            response.getWriter().write("{\"name\":\"" + data.get("name") + "\"}");
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\":\"Field 'name' not found.\"}");
        }
    }

    private Map<String, String> parsePayload(String payload) throws Exception {
        // A simple JSON parser implementation for demonstration purposes
        Map<String, String> map = new HashMap<>();
        if (payload.trim().startsWith("{") && payload.trim().endsWith("}")) {
            payload = payload.substring(1, payload.length() - 1).trim();
            String[] pairs = payload.split(",");
            for (String pair : pairs) {
                String[] keyValue = pair.split(":");
                if (keyValue.length == 2) {
                    String key = keyValue[0].trim().replace("\"", "");
                    String value = keyValue[1].trim().replace("\"", "");
                    map.put(key, value);
                }
            }
        } else {
            throw new Exception("Invalid JSON format.");
        }
        return map;
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        response.setStatus(HttpServletResponse.SC_METHOD_NOT_ALLOWED);
        response.getWriter().write("{\"error\":\"GET method not supported.\"}");
    }
}