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
        String payload = request.getParameter("payload");
        Map<String, String> data = new HashMap<>();
        
        if (payload != null && !payload.isEmpty()) {
            for (String pair : payload.split("&")) {
                int idx = pair.indexOf("=");
                data.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
        }

        response.setContentType("text/plain");
        String nameValue = data.getOrDefault("name", "Name not found");
        response.getWriter().write(nameValue);
    }
}