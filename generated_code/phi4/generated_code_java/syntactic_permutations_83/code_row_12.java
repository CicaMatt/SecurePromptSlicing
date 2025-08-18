import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/CheckName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");

        if (name != null && !name.isEmpty()) {
            response.setContentType("text/html");
            response.getWriter().write("<h2>Name received: " + name + "</h2>");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name field is required.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        response.setContentType("text/html");
        response.getWriter().write("<h1>Please use POST method to submit the name.</h1>");
    }
}


To make this code runnable:

1. Ensure you have a Java servlet container like Apache Tomcat or Jetty set up.
2. Create a web application project in your IDE and include this servlet class.
3. Deploy the application on the server.
4. Access the servlet via `http://localhost:8080/YourAppName/CheckName` using a POST request with a parameter named `name`.