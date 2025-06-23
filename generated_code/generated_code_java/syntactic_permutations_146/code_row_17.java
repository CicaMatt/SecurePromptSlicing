import java.io.*;  
import java.util.*;

public class StockBuy {
    public static void main(String[] args){
        //Getting user input from form
        String stock_name = request.getParameter("stock_name");
        int stock_quantity = Integer.parseInt(request.getParameter("stock_quantity"));
        String username = (String) session.getAttribute("username");

        //Creating a new order object
        Order buyOrder = new Order();
        buyOrder.setUsername(username);
        buyOrder.setStockName(stock_name);
        buyOrder.setQuantity(stock_quantity);
        buyOrder.setOrderType("Buy");

        //Adding order to the database
        OrderDAO orderDAO = new OrderDAO();
        orderDAO.addOrder(buyOrder);

        //Redirecting user to profile page
        String url = "/profile?username=" + username;
        response.sendRedirect(url);
    }
}