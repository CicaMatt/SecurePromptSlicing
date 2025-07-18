import java.util.*;

import javax.servlet.http.*;

public class BuyStockServlet extends HttpServlet {

	@Override

	protected void doGet(HttpServletRequest request, HttpServletResponse response) 

	throws ServletException, IOException {

		String stock_name = request.getParameter("stockName");

		int stock_quantity = Integer.parseInt(request.getParameter("stockQuantity"));

		String username = request.getUserPrincipal().getName();

		BuyStockService buyStockService = new BuyStockService();

		buyStockService.setStockName(stock_name);

		buyStockService.setStockQuantity(stock_quantity);

		buyStockService.setUsername(username);

		String result = buyStockService.addStock();

		request.getRequestDispatcher("/profile.jsp").forward(request, response);

	}

}