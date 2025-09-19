import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payloadParam = request.getParameter("payload");
        
        if (payloadParam != null && !payloadParam.isEmpty()) {
            Map<String, String> dictionary = new HashMap<>();
            loadPayloadIntoDictionary(payloadParam, dictionary);
            
            String nameValue = dictionary.getOrDefault("name", "Name not found");
            response.setContentType("text/plain");
            response.getWriter().write(nameValue);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Missing payload parameter");
        }
    }

    private void loadPayloadIntoDictionary(String payload, Map<String, String> dictionary) {
        // Assuming the payload is in key=value format separated by '&'
        String[] pairs = payload.split("&");

        for (String pair : pairs) {
            String[] keyValue = pair.split("=");
            if (keyValue.length == 2) {
                dictionary.put(keyValue[0], keyValue[1]);
            }
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To make this code runnable:
- Save it in a file named `ApiServlet.java`.
- Compile and deploy it using a Java servlet container like Apache Tomcat.
- Ensure your web application is configured to serve servlets.