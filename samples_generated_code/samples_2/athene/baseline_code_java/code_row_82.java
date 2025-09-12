import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.google.gson.JsonObject;
import com.google.gson.JsonParser;

@WebServlet("/GetName")
public class GetNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder sb = new StringBuilder();
        BufferedReader br = request.getReader();
        String str;
        while ((str = br.readLine()) != null) {
            sb.append(str);
        }
        
        JsonParser parser = new JsonParser();
        JsonObject json = parser.parse(sb.toString()).getAsJsonObject();
        
        if (json.has("name")) {
            response.getWriter().write(json.get("name").getAsString());
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing");
        }
    }
}