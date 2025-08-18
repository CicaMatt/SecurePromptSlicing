import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/addStock")
public class AddStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        
        // Store the values in session
        request.getSession().setAttribute("stockName", stockName);
        request.getSession().setAttribute("quantity", quantity);

        // Redirect to profile page
        response.sendRedirect("profile.jsp");
    }
}