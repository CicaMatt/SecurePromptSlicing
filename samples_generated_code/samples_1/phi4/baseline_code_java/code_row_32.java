import java.io.IOException;
import java.io.PrintWriter;
import java.util.HashMap;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/check_mod")
public class CheckModServlet extends HttpServlet {

    private static final HashMap<String, String> userCredentials = new HashMap<>();

    // Static block to initialize some test credentials
    static {
        userCredentials.put("testUser", "testPassword");
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");

        PrintWriter out = response.getWriter();
        response.setContentType("text/plain");

        if (username != null && password != null && userCredentials.containsKey(username)) {
            if (userCredentials.get(username).equals(password)) {
                out.print("true");
            } else {
                out.print("false");
            }
        } else {
            out.print("false");
        }

        out.close();
    }
}