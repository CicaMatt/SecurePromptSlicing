public class LoginServlet extends HttpServlet {
    public void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        request.getSession().setAttribute("username", null);
        RequestDispatcher view = request.getRequestDispatcher("/login.jsp");
        view.forward(request, response);
    }
    public void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
        String username = request.getParameter("username");
        String password = request.getParameter("password");
        if (username.equals("admin") && password.equals("admin")) {
            request.getSession().setAttribute("username", username);
            RequestDispatcher view = request.getRequestDispatcher("/secret.jsp");
            view.forward(request, response);
        } else {
            RequestDispatcher view = request.getRequestDispatcher("/login.jsp");
            view.include(request, response);
        }
    }
}