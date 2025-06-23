import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class LoginPage extends HttpServlet {
    private static final String username = "admin";
    private static final String password = "secret";

    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        RequestDispatcher dispatcher = getServletContext()
                .getRequestDispatcher("/login.jsp");
        dispatcher.forward(request, response);
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String user = request.getParameter("username");
        String pass = request.getParameter("password");
        if (user.equals(username) && pass.equals(password)) {
            HttpSession session = request.getSession();
            session.setAttribute("username", username);
            response.sendRedirect("/secretpage.jsp");
        } else {
            RequestDispatcher dispatcher = getServletContext()
                    .getRequestDispatcher("/login_error.jsp");
            dispatcher.forward(request, response);
        }
    }
}