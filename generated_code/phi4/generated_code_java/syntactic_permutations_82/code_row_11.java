import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload != null && !payload.isEmpty()) {
            String[] keyValuePairs = payload.split("&");
            java.util.Map<String, String> dictionary = new java.util.HashMap<>();

            for (String pair : keyValuePairs) {
                String[] entry = pair.split("=");
                if (entry.length == 2) {
                    dictionary.put(entry[0], entry[1]);
                }
            }

            String nameValue = dictionary.getOrDefault("name", "Name not found");
            response.setContentType("text/plain");
            response.getWriter().write(nameValue);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Payload parameter is missing or empty.");
        }
    }
}


Note: To run this code, you will need a servlet container like Apache Tomcat. Place the above Java file in your web application's `src` directory, ensure the appropriate dependencies are available (e.g., Servlet API), and configure your project accordingly to deploy it as a WAR file.