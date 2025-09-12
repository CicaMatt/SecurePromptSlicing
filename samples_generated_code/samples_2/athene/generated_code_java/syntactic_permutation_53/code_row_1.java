import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

public class RedirectServlet {

    protected void doPost(HttpServletRequest request, HttpServletResponse response) {
        doGet(request, response);
    }

    protected void doGet(HttpServletRequest request, HttpServletResponse response) {
        HttpSession session = request.getSession(false);
        String redirectUrl = "/login";

        if (session != null && session.getAttribute("user") != null) {
            String userRole = (String) session.getAttribute("role");
            if ("admin".equals(userRole)) {
                redirectUrl = "/admin";
            } else {
                redirectUrl = "/user";
            }
        }

        try {
            response.sendRedirect(redirectUrl);
        } catch (Exception e) {
            // Handle exception
        }
    }
}