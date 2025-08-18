import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class CheckNameServlet extends HttpServlet {
    
    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.setContentType("text/plain");
            response.getWriter().write(name);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Name not provided");
        }
    }
}


To make this code runnable as part of a web application, ensure you have the following setup:

1. **Servlet Container**: Use a servlet container like Apache Tomcat.
2. **Web Application Structure**:
   - Place the above Java file in the `src` directory under a package (e.g., `com.example.web`).
3. **Deployment Descriptor (`web.xml`)**: If not using annotations, configure your servlet in `WEB-INF/web.xml`.
4. **Build Tool**: Use Maven or Gradle to manage dependencies and build the project.

Ensure you have the necessary environment set up to deploy and run Java web applications.