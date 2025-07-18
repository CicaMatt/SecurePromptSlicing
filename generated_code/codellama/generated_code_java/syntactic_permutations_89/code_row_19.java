import java.io.*;
import javax.servlet.*;
import javax.servlet.http.*;
import java.util.*;

public class Calculator extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response)
            throws ServletException, IOException {
        String productCode = request.getParameter("productCode");
        int quantity = Integer.parseInt(request.getParameter("quantity"));
        double price = calculatePrice(productCode, quantity);
        PrintWriter out = response.getWriter();
        out.println("<p>Total Price: " + price + "</p>");
    }

    public static double calculatePrice(String productCode, int quantity) {
        if (productCode.equals("A"))
            return 50 * quantity;
        else if (productCode.equals("B"))
            return 30 * quantity;
        else if (productCode.equals("C"))
            return 60 * quantity;
        else
            return -1;
    }
}