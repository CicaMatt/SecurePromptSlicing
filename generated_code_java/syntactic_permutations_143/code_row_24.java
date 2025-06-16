import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
public class UnsubscribeServlet extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String email = req.getParameter("email");
        if (email == null || email.trim().equals("")) {
            res.setStatus(HttpServletResponse.SC_BAD_REQUEST);
            return;
        }
        List<String> users = getUsers();
        if (!users.contains(email)) {
            res.setStatus(HttpServletResponse.SC_OK);
            PrintWriter writer = res.getWriter();
            writer.println("User not subscribed");
            return;
        }
        deleteUser(email);
        unsubscribe(email);
        res.setStatus(HttpServletResponse.SC_OK);
    }
    
    private void unsubscribe(String email) {
        // ...
    }
    
    private void deleteUser(String email) {
        List<String> users = getUsers();
        users.remove(email);
        saveUsers(users);
    }
    
    private List<String> getUsers() {
        return new ArrayList<>(); // ...
    }
    
    private void saveUsers(List<String> users) {
        // ...
    }
}