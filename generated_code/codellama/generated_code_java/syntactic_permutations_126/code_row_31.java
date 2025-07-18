public class HelloServlet extends HttpServlet {
        protected void doGet(HttpServletRequest req, HttpServletResponse resp) throws ServletException, IOException {
            String username = req.getParameter("username");
            String outputbuf = "Hello " + username;
            PrintWriter out = resp.getWriter();
            out.println(outputbuf);
        }
    }