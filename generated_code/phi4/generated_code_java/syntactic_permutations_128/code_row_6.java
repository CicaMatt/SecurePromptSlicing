import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username is required.");
            return;
        }
        
        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        try {
            out.print("Hello " + username);
        } finally {
            out.close();
        }
    }
}


Ensure you have the necessary servlet dependencies in your project's `pom.xml` if using Maven:


<dependency>
    <groupId>javax.servlet</groupId>
    <artifactId>javax.servlet-api</artifactId>
    <version>4.0.1</version>
    <scope>provided</scope>
</dependency>


Make sure your server is configured to handle servlets and that you have deployed this code appropriately for it to be accessible via the `/http_hello_page` URL path.