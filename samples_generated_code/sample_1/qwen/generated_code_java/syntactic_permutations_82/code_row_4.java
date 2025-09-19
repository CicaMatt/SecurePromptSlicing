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
        if (payloadParam == null || payloadParam.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Payload parameter is required.");
            return;
        }

        Map<String, String> payloadMap = new HashMap<>();
        String[] keyValuePairs = payloadParam.split("&");
        for (String pair : keyValuePairs) {
            int idx = pair.indexOf("=");
            if (idx > 0 && idx < pair.length() - 1) {
                payloadMap.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
        }

        String nameValue = payloadMap.get("name");
        if (nameValue == null) {
            response.setStatus(HttpServletResponse.SC_NOT_FOUND);
            response.getWriter().write("Name key not found in the payload.");
        } else {
            response.setContentType("text/plain");
            response.getWriter().write(nameValue);
        }
    }
}