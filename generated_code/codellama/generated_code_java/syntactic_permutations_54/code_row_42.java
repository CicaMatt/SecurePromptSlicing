<details><summary>Click Here</summary>
<p>


import java.io.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;

@WebServlet(urlPatterns = {"/login"})
public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (isAdmin(username, password)) {
            request.setAttribute("username", username);
            request.getRequestDispatcher("/admin_page").forward(request, response);
        } else {
            response.sendRedirect("login?error=true");
        }
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (isAdmin(username, password)) {
            request.setAttribute("username", username);
            request.getRequestDispatcher("/admin_page").forward(request, response);
        } else {
            response.sendRedirect("login?error=true");
        }
    }
}

</p>
</details>