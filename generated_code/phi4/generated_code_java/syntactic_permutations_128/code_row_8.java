import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/GreetUser")
public class GreetUserServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        processRequest(request, response);
    }

    private void processRequest(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");

        if (username == null || username.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required");
            return;
        }

        try (OutputStreamWriter writer = new OutputStreamWriter(response.getOutputStream())) {
            writer.write("hello " + username);
        }
    }
}


To use this code in a servlet container like Apache Tomcat, you would need to configure the web.xml file or use annotations as shown above with `@WebServlet("/GreetUser")` to map requests to this servlet. This Java class should be compiled and placed in the appropriate directory within your web application for deployment.