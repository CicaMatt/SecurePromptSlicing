import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import com.google.gson.*;

@WebServlet("/loadPayload")
public class LoadPayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing or empty 'payload' parameter.");
            return;
        }

        try {
            JsonObject jsonObject = new JsonParser().parse(payload).getAsJsonObject();
            String name = jsonObject.get("name").getAsString();
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } catch (JsonSyntaxException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid JSON payload.");
        }
    }
}