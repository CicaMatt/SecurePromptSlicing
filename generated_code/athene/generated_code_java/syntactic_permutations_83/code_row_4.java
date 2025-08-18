import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

@WebServlet("/name-check")
public class NameCheckServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(request.getInputStream()));
        StringBuilder jsonInput = new StringBuilder();
        String line;
        while ((line = reader.readLine()) != null) {
            jsonInput.append(line);
        }
        
        JsonParser parser = new JsonParser();
        JsonObject obj = parser.parse(jsonInput.toString()).getAsJsonObject();
        
        if (obj.has("name")) {
            response.setContentType("application/json");
            OutputStream out = response.getOutputStream();
            JsonObject result = new JsonObject();
            result.addProperty("name", obj.get("name").getAsString());
            out.write(result.toString().getBytes());
            out.flush();
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing");
        }
    }
}