import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import org.json.JSONObject;

@WebServlet("/loadPayload")
public class PayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload != null) {
            JSONObject json = new JSONObject(payload);
            String name = json.optString("name", "Unknown");
            response.getWriter().write(name);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing.");
        }
    }
}