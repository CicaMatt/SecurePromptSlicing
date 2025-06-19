public class HelloWorldServlet extends HttpServlet {
  protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
    String username = req.getParameter("username");
    String outputbuf = "<html><body>Hello " + username + "</body></html>";
    resp.setContentType("text/html");
    PrintWriter out = resp.getWriter();
    out.println(outputbuf);
  }
}