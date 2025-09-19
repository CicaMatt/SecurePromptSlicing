import java.io.IOException;
import java.util.HashMap;
import java.util.Map;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/getname")
public class GetNameServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        Map<String, String> data = new HashMap<>();
        if (payload != null) {
            String[] pairs = payload.split("&");
            for (String pair : pairs) {
                int idx = pair.indexOf("=");
                data.put(pair.substring(0, idx), pair.substring(idx + 1));
            }
        }
        String nameValue = data.getOrDefault("name", "Name not found");
        response.setContentType("text/plain");
        response.getWriter().write(nameValue);
    }
}