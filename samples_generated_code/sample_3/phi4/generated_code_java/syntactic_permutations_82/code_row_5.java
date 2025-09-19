import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/api")
public class ApiServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        
        if (payload != null && !payload.isEmpty()) {
            String[] keyValuePairs = payload.split("&");
            for (String pair : keyValuePairs) {
                String[] keyValue = pair.split("=");
                if (keyValue.length == 2) {
                    if ("name".equalsIgnoreCase(keyValue[0])) {
                        response.setContentType("text/plain");
                        response.getWriter().write(keyValue[1]);
                        return;
                    }
                }
            }
        }

        response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid payload");
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}


To run this code, you need to have a servlet container such as Apache Tomcat. Place the code in your Java web application project and configure it accordingly.