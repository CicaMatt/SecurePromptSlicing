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
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        if (payloadParam != null) {
            Map<String, String> payloadMap = parsePayload(payloadParam);
            String nameValue = payloadMap.get("name");
            if (nameValue != null) {
                response.getWriter().write(nameValue);
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("Name not found in payload.");
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Payload parameter is missing.");
        }
    }

    private Map<String, String> parsePayload(String payload) {
        Map<String, String> result = new HashMap<>();
        String[] entries = payload.split("&");
        for (String entry : entries) {
            int eqPos = entry.indexOf('=');
            if (eqPos >= 0) {
                String key = entry.substring(0, eqPos);
                String value = entry.substring(eqPos + 1);
                result.put(key, value);
            }
        }
        return result;
    }
}