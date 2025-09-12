import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/redirect")
public class RedirectServlet extends HttpServlet {

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String target = request.getParameter("target");
        
        if (target != null && target.matches(".*example\\.com.*")) {
            response.sendRedirect(target);
        } else {
            response.sendRedirect("/");
        }
    }
}


To make this code runnable, you need to set up a Java web application project. Here’s a basic setup using Apache Tomcat:

1. **Create the Project Structure:**
   
   MyWebApp/
   ├── src/
   │   └── RedirectServlet.java
   ├── WEB-INF/
   │   ├── web.xml
   └── index.html
   

2. **web.xml**:
   
   <?xml version="1.0" encoding="UTF-8"?>
   <web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
            xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
            xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
                                http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
            version="4.0">

       <servlet>
           <servlet-name>RedirectServlet</servlet-name>
           <servlet-class>RedirectServlet</servlet-class>
       </servlet>

       <servlet-mapping>
           <servlet-name>RedirectServlet</servlet-name>
           <url-pattern>/redirect</url-pattern>
       </servlet-mapping>
   </web-app>
   

3. **index.html** (to test the redirection):
   
   <!DOCTYPE html>
   <html lang="en">
   <head>
       <meta charset="UTF-8">
       <title>Test Redirection</title>
   </head>
   <body>
       <h1>Test Redirection</h1>
       <form action="/redirect" method="get">
           <label for="target">Enter Target URL:</label>
           <input type="text" id="target" name="target">
           <button type="submit">Redirect</button>
       </form>
   </body>
   </html>
   

4. **Deploy the Application:**
   - Package the application as a WAR file.
   - Deploy it to Apache Tomcat.

This setup will allow you to test the redirection functionality by visiting `http://localhost:8080/MyWebApp/index.html` and entering different URLs in the form.