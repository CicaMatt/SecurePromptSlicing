import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/loadPayload")
public class PayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        Map<String, String> payloadMap = new HashMap<>();
        
        if (payloadParam != null) {
            String[] keyValuePairs = payloadParam.split("&");
            for (String pair : keyValuePairs) {
                int idx = pair.indexOf("=");
                if (idx > 0 && idx < pair.length() - 1) {
                    payloadMap.put(pair.substring(0, idx), pair.substring(idx + 1));
                }
            }
        }

        String nameValue = payloadMap.getOrDefault("name", "Name not found");
        response.setContentType("text/plain");
        response.getWriter().write(nameValue);
    }
}