import java.io.IOException;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/ChangeEmail")
public class ChangeEmailServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    // This is a simple in-memory user store for demonstration purposes.
    private HashMap<String, User> users = new HashMap<>();

    public void init() {
        // Initial dummy user
        users.put("user@example.com", new User("user@example.com", "password123"));
    }

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        HttpSession session = request.getSession(false);

        if (session == null || session.getAttribute("email") == null) {
            response.sendRedirect("login.html");
            return;
        }

        String currentEmail = (String) session.getAttribute("email");
        User currentUser = users.get(currentEmail);

        String newEmail = request.getParameter("newEmail");
        String confirmPassword = request.getParameter("confirmPassword");
        String password = request.getParameter("password");

        if (!currentUser.getPassword().equals(password)) {
            response.getWriter().println("<html><body>Email change failed: Incorrect password.</body></html>");
            return;
        }

        if (newEmail == null || newEmail.trim().isEmpty() || !newEmail.equals(currentEmail) && users.containsKey(newEmail)) {
            response.getWriter().println("<html><body>Email change failed: Invalid or already taken email address.</body></html>");
            return;
        }
        
        if (!confirmPassword.equals(password)) {
            response.getWriter().println("<html><body>Email change failed: Password confirmation does not match.</body></html>");
            return;
        }

        users.remove(currentEmail);
        currentUser.setEmail(newEmail);
        users.put(newEmail, currentUser);

        session.setAttribute("email", newEmail);

        response.sendRedirect("emailChanged.html");
    }
}

class User {
    private String email;
    private String password;

    public User(String email, String password) {
        this.email = email;
        this.password = password;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    public String getPassword() {
        return password;
    }
}


To make this code runnable, you'll need a basic setup with an appropriate Servlet container (like Apache Tomcat), and some additional files:

1. **`web.xml`** to configure the servlet if using older versions of Tomcat or not using annotations.
2. **HTML files**: `login.html`, `changeEmailForm.html`, and `emailChanged.html`.

Here's a basic example for each:

#### login.html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Login</title>
</head>
<body>
    <form action="Login" method="post">
        Email: <input type="text" name="email"><br>
        Password: <input type="password" name="password"><br>
        <button type="submit">Login</button>
    </form>
</body>
</html>


#### changeEmailForm.html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Change Email</title>
</head>
<body>
    <h2>Change Your Email</h2>
    <form action="ChangeEmail" method="post">
        New Email: <input type="text" name="newEmail"><br>
        Password (for confirmation): <input type="password" name="confirmPassword"><br>
        Current Password: <input type="password" name="password"><br>
        <button type="submit">Change Email</button>
    </form>
</body>
</html>


#### emailChanged.html

<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <title>Email Changed</title>
</head>
<body>
    <h2>Your email has been successfully changed.</h2>
</body>
</html>