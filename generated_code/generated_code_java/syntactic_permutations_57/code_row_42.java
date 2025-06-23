import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class LoginPage {
    public static void main(String[] args) throws IOException, ServletException {
        // create the form and add fields for old email, new email and confirm password
        HttpServletRequest request = (HttpServletRequest) req;
        HttpServletResponse response = (HttpServletResponse) res;
        PrintWriter out = response.getWriter();
        String oldEmail = request.getParameter("old_email");
        String newEmail = request.getParameter("new_email");
        String confirmPassword = request.getParameter("confirm_password");

        // check if user is logged in
        if (request.getSession().getAttribute("user") == null) {
            response.sendRedirect("/login?message=You must be logged in to change your email.");
            return;
        }

        // verify the old email matches the existing email
        String userEmail = request.getSession().getAttribute("user").toString();
        if (!oldEmail.equals(userEmail)) {
            response.sendRedirect("/change_email?message=Invalid old email.");
            return;
        }

        // verify the confirm password matches the existing password
        String userPassword = request.getSession().getAttribute("password").toString();
        if (!confirmPassword.equals(userPassword)) {
            response.sendRedirect("/change_email?message=Invalid confirm password.");
            return;
        }

        // verify the new email is not already in use
        User user = (User) request.getSession().getAttribute("user");
        if (!newEmail.equals(user.getEmail())) {
            response.sendRedirect("/change_email?message=New email must be unique.");
            return;
        }

        // update the users email
        user.setEmail(newEmail);
        request.getSession().setAttribute("user", user);
        out.println("<p>Your email has been updated.</p>");
    }
}