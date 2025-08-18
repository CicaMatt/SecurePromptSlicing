import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Paths;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            
            // Read the contents of hello.html
            String templateContent;
            try {
                templateContent = new String(Files.readAllBytes(Paths.get("src/main/webapp/templates/hello.html")));
            } catch (IOException e) {
                throw new ServletException("Error reading template file", e);
            }

            // Replace placeholder with actual username
            String output = templateContent.replace("<%username%>", username);

            // Set response content type and write the rendered content to response
            response.setContentType("text/html");
            response.getWriter().write(output);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "User not found or invalid URL");
        }
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        doGet(request, response);
    }
}



<!-- src/main/webapp/templates/hello.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, <%username%>!</h1>
</body>
</html>


**Note:** Ensure that the `hello.html` file is placed in the `src/main/webapp/templates/` directory of your web application. This setup assumes you are using a Java servlet-based web application framework such as Apache Tomcat or any other compatible server for running Servlets.