import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class BuyOrderServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stock_name");
        String stock_quantity = request.getParameter("stock_quantity");
        String username = (String) request.getSession().getAttribute("username");

        // Assuming you have a method to insert the buy order into the database
        insertBuyOrder(username, stock_name, Integer.parseInt(stock_quantity));

        response.sendRedirect("profile.jsp");
    }

    private void insertBuyOrder(String username, String stockName, int quantity) {
        // Dummy implementation for inserting buy order
        System.out.println("Inserting buy order for " + username + ": " + stockName + " x " + quantity);
        // Here you would typically have database logic to insert the order
    }
}