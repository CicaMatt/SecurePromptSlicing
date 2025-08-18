import java.io.*;
import java.net.http.*;
import java.net.URI;
import java.util.HashMap;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String payload = request.getParameter("payload");
        HashMap<String, String> params = new HashMap<>();
        
        if (payload != null && !payload.isEmpty()) {
            String[] keyValuePairs = payload.split("&");
            for (String pair : keyValuePairs) {
                String[] entry = pair.split("=");
                if (entry.length > 1) {
                    params.put(entry[0], entry[1]);
                }
            }
        }

        response.setContentType("application/json");
        response.getWriter().println(new ObjectMapper().writeValueAsString(params));
    }
}