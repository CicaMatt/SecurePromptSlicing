import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;

public class BuyStockServlet extends HttpServlet {
    protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String stock_name = request.getParameter("stock_name");
        int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) request.getSession().getAttribute("username");

        // Here you would typically insert the buy order into a database
        // For demonstration purposes, we'll just print it out

        System.out.println("Username: " + username);
        System.out.println("Stock Name: " + stock_name);
        System.out.println("Stock Quantity: " + stock_quantity);

        response.sendRedirect("profile.jsp");
    }
}