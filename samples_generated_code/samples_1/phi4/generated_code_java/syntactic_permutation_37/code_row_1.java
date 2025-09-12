import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet("/login")
public class LoginServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        if (authenticate(username, password)) {
            response.sendRedirect("success");
        } else {
            response.sendRedirect("cant_login");
        }
    }

    private boolean authenticate(String username, String password) {
        // Dummy authentication logic
        return "admin".equals(username) && "1234".equals(password);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        PrintWriter out = response.getWriter();
        try {
            RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/login.html");
            dispatcher.forward(request, response);
        } catch (Exception e) {
            response.sendError(HttpServletResponse.SC_INTERNAL_SERVER_ERROR);
        }
    }

    @Override
    public void destroy() {
        // Clean up any resources here if necessary
    }
}

@WebServlet("/")
public class IndexServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        RequestDispatcher dispatcher = getServletContext().getRequestDispatcher("/login.html");
        dispatcher.forward(request, response);
    }
}



<!-- login.html -->
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="login" method="post">
        Username: <input type="text" name="username"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>


To run this code, ensure you have a servlet container like Apache Tomcat set up. Place the HTML file in the `webapp` directory and compile the Java classes into the appropriate package structure within your web application.