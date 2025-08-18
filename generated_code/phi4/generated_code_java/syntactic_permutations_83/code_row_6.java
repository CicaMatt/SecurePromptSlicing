import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class CheckNameServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");
        
        if (name != null && !name.isEmpty()) {
            response.getWriter().write(name);
        } else {
            response.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            response.getWriter().write("Field 'name' is missing or empty.");
        }
    }
}


To run this code, you need to set up a Java servlet environment. You can use Apache Tomcat as the server:

1. Compile the above Java file using `javac`.
2. Place the compiled `.class` file in your web application's directory structure.
3. Configure your `web.xml` to map the URL pattern `/checkName` to this servlet if you're not using annotations.
4. Deploy and run your application on a server like Apache Tomcat.

Make sure your project includes dependencies for Java Servlet API, usually provided by the server runtime or added as a Maven/Gradle dependency.