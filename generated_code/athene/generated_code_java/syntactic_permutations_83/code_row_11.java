import java.io.*;
import javax.servlet.http.*;
import com.google.gson.*;

public class NameServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        StringBuilder sb = new StringBuilder();
        String line;
        BufferedReader reader = request.getReader();
        while ((line = reader.readLine()) != null) {
            sb.append(line);
        }
        String jsonPayload = sb.toString();
        
        JsonObject jsonObject = JsonParser.parseString(jsonPayload).getAsJsonObject();
        if (jsonObject.has("name")) {
            response.setContentType("application/json");
            response.getWriter().write("{\"name\": \"" + jsonObject.get("name").getAsString() + "\"}");
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("{\"error\": \"Field 'name' is missing\"}");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.sendError(HttpServletResponse.SC_METHOD_NOT_ALLOWED, "Method Not Allowed");
    }
}