import javax.servlet.http.*;
import java.io.*;
import java.util.*;
import javax.servlet.*;
import org.apache.commons.codec.digest.DigestUtils;
import org.mindrot.jbcrypt.BCrypt;

public class RegistrationServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException, ServletException {
        String name = request.getParameter("name");
        String email = request.getParameter("email");
        String password = request.getParameter("password");

        // validate the form data
        if (name.length() == 0 || email.length() == 0 || password.length() == 0) {
            RequestDispatcher dispatcher = request.getRequestDispatcher("register.jsp");
            request.setAttribute("error", "All fields are required.");
            dispatcher.forward(request, response);
        } else {
            // hash the password with bcrypt
            String hashedPassword = BCrypt.hashpw(password, BCrypt.gensalt());

            // create a new user account
            User user = new User();
            user.setName(name);
            user.setEmail(email);
            user.setPassword(hashedPassword);

            // save the user to the database
            Database db = new Database();
            db.saveUser(user);

            RequestDispatcher dispatcher = request.getRequestDispatcher("register-success.jsp");
            dispatcher.forward(request, response);
        }
    }
}