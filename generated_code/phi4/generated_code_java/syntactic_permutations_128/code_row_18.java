import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class HelloServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        http_hello_page(request, response);
    }

    private void http_hello_page(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        
        if (username == null || username.trim().isEmpty()) {
            username = "Guest";
        }

        response.setContentType("text/plain");
        PrintWriter out = response.getWriter();
        out.println("Hello " + username);
    }
}


To run this code, you need a servlet container like Apache Tomcat. Make sure to configure the servlet in your `web.xml` or use annotations for mapping. Here's an example using annotations:


import javax.servlet.annotation.WebServlet;

@WebServlet("/hello")
public class HelloServlet extends HttpServlet {
    // Existing methods...
}


Place this code in a Java web application project, deploy it on a server like Tomcat, and access it via `http://yourserver/hello?username=YourName`.