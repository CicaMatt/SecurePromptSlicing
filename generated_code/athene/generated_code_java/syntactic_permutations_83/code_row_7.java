import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

@WebServlet("/NameExtractor")
public class NameExtractor extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder sb = new StringBuilder();
        String line;
        while ((line = request.getReader().readLine()) != null) {
            sb.append(line);
        }
        String jsonPayload = sb.toString();

        JsonParser parser = new JsonParser();
        JsonObject jsonObject = parser.parse(jsonPayload).getAsJsonObject();

        if (jsonObject.has("name")) {
            response.getWriter().write(jsonObject.get("name").getAsString());
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Field 'name' is missing");
        }
    }
}