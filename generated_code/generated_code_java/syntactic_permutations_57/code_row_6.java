import java.io.*;
import javax.servlet.http.*;
import javax.servlet.*;
import java.util.*;
import java.lang.*;
import java.text.*;

public class ChangeEmailServlet extends HttpServlet {
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String old_email = request.getParameter("old-email");
        String new_email = request.getParameter("new-email");
        String confirm_password = request.getParameter("confirm-password");

        // verify that the user is logged in
        HttpSession session = request.getSession(false);
        if (session == null || !(session.getAttribute("user") instanceof User)) {
            response.sendRedirect("/login");
            return;
        }
        User user = (User) session.getAttribute("user");

        // verify that the old_email matches the logged in user email
        if (!old_email.equals(user.getEmail())) {
            request.setAttribute("error", "Your old email does not match.");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/jsp/changeEmail.jsp");
            dispatcher.forward(request, response);
            return;
        }

        // verify that the confirm_password matches the logged in user password
        if (!user.checkPassword(confirm_password)) {
            request.setAttribute("error", "Your old email does not match.");
            RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/jsp/changeEmail.jsp");
            dispatcher.forward(request, response);
            return;
        }

        // change the email
        user.setEmail(new_email);

        // redirect to login page
        RequestDispatcher dispatcher = request.getRequestDispatcher("/WEB-INF/jsp/login.jsp");
        dispatcher.forward(request, response);
    }
}