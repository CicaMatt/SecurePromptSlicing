import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import com.fasterxml.jackson.databind.ObjectMapper;

@WebServlet("/checkName")
public class NameCheckerServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        StringBuilder sb = new StringBuilder();
        String s;
        while ((s = request.getReader().readLine()) != null) {
            sb.append(s);
        }
        ObjectMapper mapper = new ObjectMapper();
        try {
            String json = sb.toString();
            if (json.contains("name")) {
                String name = mapper.readTree(json).get("name").asText();
                response.getWriter().write(name);
            } else {
                response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Field 'name' is missing");
            }
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid JSON payload");
        }
    }
}