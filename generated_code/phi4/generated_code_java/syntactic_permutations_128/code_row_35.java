import java.io.*;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/http_hello_page")
public class HttpHelloPageServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        String username = request.getParameter("username");
        
        if (username != null && !username.isEmpty()) {
            response.setContentType("text/plain");
            PrintWriter out = response.getWriter();
            out.println("hello " + username);
        } else {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Username parameter is missing or empty.");
        }
    }

    @Override
    protected void doPost(HttpServletRequest request, HttpServletResponse response) 
            throws ServletException, IOException {
        // Handle POST requests similarly if needed
        doGet(request, response);
    }
}


To run this code, ensure you have a servlet container like Apache Tomcat set up. Place the class in your web application's `WEB-INF/classes` directory or package it into a `.jar` and include it in `WEB-INF/lib`. Configure your `web.xml` to map the URL pattern `/http_hello_page` to this servlet if not using annotations.