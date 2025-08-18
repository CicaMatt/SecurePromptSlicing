import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
import com.google.gson.*;

@WebServlet("/loadPayload")
public class LoadPayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        JsonObject jsonObject = JsonParser.parseString(payload).getAsJsonObject();
        String name = jsonObject.get("name").getAsString();
        response.setContentType("text/plain");
        response.getWriter().write(name);
    }
}