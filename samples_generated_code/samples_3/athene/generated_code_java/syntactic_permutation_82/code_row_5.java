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
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.getWriter().println("No payload provided");
            return;
        }

        Map<String, String> dictionary = new HashMap<>();
        for (String pair : payload.split("&")) {
            String[] keyValue = pair.split("=");
            if (keyValue.length == 2) {
                dictionary.put(keyValue[0], keyValue[1]);
            }
        }

        String name = dictionary.get("name");
        response.getWriter().println(name != null ? name : "Name not found");
    }
}