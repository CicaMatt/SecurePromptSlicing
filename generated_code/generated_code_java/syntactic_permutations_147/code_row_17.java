import javax.servlet.http.*;  
    public class buy_order extends HttpServlet {  
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
        String stockname=request.getParameter("stock_name");  
        int quantity=Integer.parseInt(request.getParameter("quantity"));  
        //insert data into database  
        response.sendRedirect("stock_view");  
    }  
}