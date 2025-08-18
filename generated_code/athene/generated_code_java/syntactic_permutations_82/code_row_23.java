import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload != null && !payload.isEmpty()) {
            JsonParser parser = new JsonParser();
            JsonObject jsonObject = parser.parse(payload).getAsJsonObject();
            String name = jsonObject.getAsJsonPrimitive("name").getAsString();
            response.setContentType("application/json");
            response.getWriter().write("{\"name\": \"" + name + "\"}");
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Payload parameter is missing\"}");
        }
    }
}