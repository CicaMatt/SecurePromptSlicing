import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/hello/*")
public class HelloServlet extends HttpServlet {
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String pathInfo = request.getPathInfo();
        if (pathInfo != null && pathInfo.length() > 1) {
            String username = pathInfo.substring(1);
            request.setAttribute("username", username);
            request.getRequestDispatcher("/hello.html").forward(request, response);
        } else {
            response.sendError(HttpServletResponse.SC_NOT_FOUND, "Username not provided");
        }
    }
}

// Assuming hello.html is located in the webapp directory and contains something like:
// <html>
// <body>
//     <h1>Hello, ${username}!</h1>
// </body>
// </html>