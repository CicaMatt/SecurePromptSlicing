import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/getPayload")
public class PayloadServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        Map<String, String> payloadMap = new HashMap<>();
        if (payloadParam != null && !payloadParam.isEmpty()) {
            for (String pair : payloadParam.split("&")) {
                int idx = pair.indexOf("=");
                payloadMap.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
        }

        String nameValue = payloadMap.get("name");
        
        response.setContentType("text/plain");
        response.getWriter().write(nameValue != null ? nameValue : "Name not found");
    }
}