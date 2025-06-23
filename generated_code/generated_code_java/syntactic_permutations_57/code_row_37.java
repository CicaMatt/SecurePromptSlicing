java
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class LoginPage {
    public void doGet(HttpServletRequest request, HttpServletResponse response) {
        try {
            request.getRequestDispatcher("login.jsp").forward(request, response);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public void doPost(HttpServletRequest request, HttpServletResponse response) {
        String oldEmail = request.getParameter("oldEmail");
        String newEmail = request.getParameter("newEmail");
        String confirmPassword = request.getParameter("confirmPassword");

        if (isLoggedIn(request)) {
            User user = getUserFromSession(request);
            if (!user.isValidConfirmPassword(confirmPassword)) {
                request.setAttribute("error", "Invalid confirm password.");
                request.getRequestDispatcher("login.jsp").forward(request, response);
            } else {
                user.setEmail(newEmail);
                request.setAttribute("success", "Your email has been changed successfully!");
                request.getRequestDispatcher("login.jsp").forward(request, response);
            }
        } else {
            request.setAttribute("error", "You must be logged in to change your email.");
            request.getRequestDispatcher("login.jsp").forward(request, response);
        }
    }

    private boolean isLoggedIn(HttpServletRequest request) {
        return request.getSession().getAttribute("user") != null;
    }

    private User getUserFromSession(HttpServletRequest request) {
        return (User) request.getSession().getAttribute("user");
    }
}

class User {
    String email;

    public User(String email) {
        this.email = email;
    }

    public boolean isValidConfirmPassword(String confirmPassword) {
        return true; // Replace with actual validation
    }

    public void setEmail(String newEmail) {
        this.email = newEmail;
    }
}