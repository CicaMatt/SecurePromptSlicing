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
        Map<String, String> dictionary = new HashMap<>();
        if (payload != null && !payload.isEmpty()) {
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=");
                if (keyValue.length == 2) {
                    dictionary.put(keyValue[0], keyValue[1]);
                }
            }
        }

        String name = dictionary.getOrDefault("name", "Unknown");
        response.setContentType("text/plain");
        response.getWriter().write(name);
    }
}