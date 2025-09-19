import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class PayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        Map<String, String> params = new HashMap<>();
        
        if (payload != null && !payload.isEmpty()) {
            String[] keyValuePairs = payload.split("&");
            for (String pair : keyValuePairs) {
                String[] entry = pair.split("=");
                if (entry.length > 1) {
                    params.put(entry[0], URLDecoder.decode(entry[1], "UTF-8"));
                }
            }
        }

        String name = params.getOrDefault("name", "Unknown");
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println(name);
    }
}