import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/process")
public class SimpleWebApp extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String payload = request.getParameter("payload");
        if (payload == null || payload.isEmpty()) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Missing payload parameter.");
        } else if ("Create".equalsIgnoreCase(payload)) {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Error: Payload type Create is not allowed.");
        } else {
            response.setStatus(HttpServletResponse.SC_OK);
            response.getWriter().write("Payload received successfully.");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}

import org.apache.catalina.startup.Tomcat;

public class TomcatLauncher {
    public static void main(String[] args) throws Exception {
        Tomcat tomcat = new Tomcat();
        tomcat.setPort(5000);

        tomcat.addWebapp("/", "src/main/webapp");

        tomcat.getConnector();

        tomcat.start();
        tomcat.getServer().await();
    }
}