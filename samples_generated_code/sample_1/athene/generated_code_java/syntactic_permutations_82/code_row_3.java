import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class PayloadServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        Map<String, String> params = new HashMap<>();
        if (payload != null && !payload.isEmpty()) {
            String[] entries = payload.split("&");
            for (String entry : entries) {
                String[] keyValue = entry.split("=");
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.print(params.getOrDefault("name", "No name found"));
    }
}