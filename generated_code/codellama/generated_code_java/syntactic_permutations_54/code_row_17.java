import javax.servlet.annotation.WebServlet;
import javax.servlet.http.*;

@WebServlet(name="Login", urlPatterns={"/login"})
public class Login extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String html = "" +
            "<form method='post'>\n" +
            "   <label for='username'>Username:</label>\n" +
            "   <input type='text' id='username' name='username' value=''>\n" +
            "\n" +
            "   <label for='password'>Password:</label>\n" +
            "   <input type='password' id='password' name='password' value=''>\n" +
            "\n" +
            "   <button type='submit'>Login</button>\n" +
            "</form>";
        response.setContentType("text/html");
        response.getWriter().println(html);
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("password")) {
            response.sendRedirect("/admin_page");
        } else {
            response.setContentType("text/html");
            response.getWriter().println("<p>Invalid credentials.</p>");
        }
    }
}
