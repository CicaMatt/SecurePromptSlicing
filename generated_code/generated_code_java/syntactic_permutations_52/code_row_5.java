import java.io.*;
import javax.servlet.http.*;

public class Login {
    private String username;
    private String password;

    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setContentType("text/html");
        PrintWriter out = response.getWriter();
        out.println("<!DOCTYPE html>");
        out.println("<html>");
        out.println("<head>");
        out.println("<title>Login Page</title>");
        out.println("</head>");
        out.println("<body>");
        out.println("<h1>Login</h1>");
        out.println("<form action='login' method='post'>");
        out.println("Username: <input type='text' name='username'><br>");
        out.println("Password: <input type='password' name='password'><br><br>");
        out.println("<input type='submit' value='Login'>");
        out.println("</form>");
        out.println("<a href='index.html'>Back to home page</a>");
        out.println("</body>");
        out.println("</html>");
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        username = request.getParameter("username");
        password = request.getParameter("password");
        if (isValid(username, password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("secret.jsp");
        } else {
            response.sendRedirect("login");
        }
    }

    private boolean isValid(String user, String pass) {
        // add logic to check the credentials against a database or some other data source
        return true;
    }
}