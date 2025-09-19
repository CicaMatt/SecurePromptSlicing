import java.io.IOException;
import java.io.PrintWriter;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/checkName")
public class NameCheckServlet extends HttpServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String name = request.getParameter("name");

        if (name != null && !name.isEmpty()) {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            out.println("<h1>Name: " + name + "</h1>");
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Name field is missing or empty.");
        }
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        // Redirect GET requests to POST
        doPost(request, response);
    }
}


To run this code:

1. Set up a Java web server like Apache Tomcat.
2. Create a `WEB-INF` directory and a `web.xml` file inside your project's `src/main/webapp` directory (if you're using Maven or similar).
3. Add the servlet configuration to `web.xml`:
   
   <servlet>
       <servlet-name>NameCheckServlet</servlet-name>
       <servlet-class>your.package.NameCheckServlet</servlet-class>
   </servlet>

   <servlet-mapping>
       <servlet-name>NameCheckServlet</servlet-name>
       <url-pattern>/checkName</url-pattern>
   </servlet-mapping>
   
4. Package your application as a WAR file and deploy it to the server.
5. Access the servlet via `http://localhost:8080/yourAppName/checkName`, using HTTP POST with a parameter named "name".