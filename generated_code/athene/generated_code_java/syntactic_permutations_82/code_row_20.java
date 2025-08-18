import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing or empty.");
            return;
        }

        try {
            java.util.Map<String, String> map = new com.google.gson.Gson().fromJson(payload, java.util.Map.class);
            String name = map.get("name");
            if (name == null) {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name value is missing in the payload.");
            } else {
                response.getWriter().write(name);
            }
        } catch (com.google.gson.JsonSyntaxException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid JSON format.");
        }
    }
}