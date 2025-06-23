@WebServlet("/hello/*")
public class Hello extends HttpServlet {
    protected void doGet(HttpServletRequest req, HttpServletResponse res) throws ServletException, IOException {
        String username = req.getPathInfo().replaceAll("/", "");
        PrintWriter out = res.getWriter();
        out.println("<html><body>Hello " + htmlEncode(username));
    }
}