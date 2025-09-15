import java.io.IOException;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

@WebServlet("/submitStock")
public class StockFormServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stockName = request.getParameter("stockName");
        String quantity = request.getParameter("quantity");

        // Redirect to profile page with stock name and quantity as parameters
        response.sendRedirect("profile.jsp?stockName=" + stockName + "&quantity=" + quantity);
    }
}
