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

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.startsWith("/hello/")) {
            String username = pathInfo.substring(6);
            renderTemplate(response, "hello.html", username);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
        }
    }

    private void renderTemplate(HttpServletResponse response, String templateFileName, String username) throws IOException {
        String templateContent = new String(Files.readAllBytes(Paths.get(templateFileName)));
        String renderedContent = templateContent.replace("${username}", username);

        response.setContentType("text/html");
        response.setCharacterEncoding("UTF-8");
        response.getWriter().write(renderedContent);
    }
}



<!-- hello.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, ${username}!</h1>
</body>
</html>


To run this code, ensure you have a Java servlet container like Apache Tomcat set up. Place the `HelloServlet` class in your web application's source directory and the `hello.html` file in the appropriate location (e.g., `webapp/WEB-INF/templates/hello.html`) or adjust paths as needed based on your project structure.