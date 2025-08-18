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
        
        if (payloadParam != null && !payloadParam.isEmpty()) {
            Map<String, String> payloadMap = loadPayloadIntoDictionary(payloadParam);
            String nameValue = payloadMap.get("name");

            if (nameValue != null) {
                response.setContentType("text/plain");
                response.getWriter().write(nameValue);
            } else {
                response.setStatus(HttpServletResponse.SC_NOT_FOUND);
                response.getWriter().write("Name not found in payload.");
            }
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Payload parameter is missing or empty.");
        }
    }

    private Map<String, String> loadPayloadIntoDictionary(String payload) {
        Map<String, String> map = new HashMap<>();
        String[] pairs = payload.split("&");
        
        for (String pair : pairs) {
            int idx = pair.indexOf("=");
            if (idx > 0 && idx < pair.length() - 1) {
                map.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
        }
        
        return map;
    }
}