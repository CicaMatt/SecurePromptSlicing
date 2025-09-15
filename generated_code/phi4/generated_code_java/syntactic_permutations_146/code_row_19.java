import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

@WebServlet("/BuyOrderServlet")
public class BuyOrderServlet extends HttpServlet {
    private static final long serialVersionUID = 1L;

    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stock_name");
        int stockQuantity;
        
        try {
            stockQuantity = Integer.parseInt(request.getParameter("stock_quantity"));
        } catch (NumberFormatException e) {
            response.sendError(HttpServletResponse.SC_BAD_REQUEST, "Invalid quantity entered.");
            return;
        }
        
        HttpSession session = request.getSession();
        String username = (String) session.getAttribute("username");
        
        if (username == null || stockName == null || stockQuantity <= 0) {
            response.sendRedirect("error_page.html");
            return;
        }

        // Insert buy order logic here
        // For example, insert into a database or any other storage system

        // Redirect to profile page
        response.sendRedirect("profile.jsp?username=" + username);
    }
}
