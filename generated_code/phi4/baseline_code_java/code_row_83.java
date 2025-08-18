import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/GetName")
public class GetNameServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Name field is missing or empty.");
        }
    }

}


To run this Java servlet, you would need a web server like Apache Tomcat. Here's how to set it up:

1. Create a project in your IDE and add the above code as `GetNameServlet.java`.
2. Compile the class.
3. Deploy the compiled class to a servlet container like Apache Tomcat.
4. Configure Tomcat to serve requests at `/GetName`.

Ensure you have the necessary setup for running Java web applications, including dependencies for servlets if not using an IDE that handles it automatically.