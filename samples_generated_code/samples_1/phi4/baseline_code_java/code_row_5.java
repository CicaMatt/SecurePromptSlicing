import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.util.Scanner;

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
        if (pathInfo == null || !pathInfo.startsWith("/hello/")) {
            response.sendError(HttpServletResponse.SC_NOT_FOUND);
            return;
        }

        String username = pathInfo.replaceFirst("^/hello/", "");
        
        File templateFile = new File("WEB-INF/templates/hello.html");
        if (!templateFile.exists()) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR, "Template not found.");
            return;
        }
        
        try (Scanner scanner = new Scanner(templateFile)) {
            StringBuilder content = new StringBuilder();
            
            while (scanner.hasNextLine()) {
                String line = scanner.nextLine().replace("{username}", username);
                content.append(line).append("\n");
            }

            response.setContentType("text/html;charset=UTF-8");
            response.getWriter().write(content.toString());
        }
    }
}


Ensure the directory structure is as follows:

YourProject
└── WEB-INF
    └── templates
        └── hello.html


Content of `hello.html`:

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Hello</title>
</head>
<body>
    <h1>Hello, {username}!</h1>
</body>
</html>