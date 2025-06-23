import java.io.File;
import javax.servlet.*;
import javax.servlet.http.*;
import javax.servlet.annotation.*;
@WebServlet(name="img", urlPatterns="/img")
public class img extends HttpServlet{
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String name = request.getParameter("name");
        File file = new File("/images/" + name);
        response.sendFile(file);
    }
}