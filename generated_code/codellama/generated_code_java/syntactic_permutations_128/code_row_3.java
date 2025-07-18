public class HelloServlet extends HttpServlet {
        protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException {
            PrintWriter writer = res.getWriter();
            String name = req.getParameter("username");
            if (name == null) {
                writer.println("hello world");
            } else {
                writer.println("hello " + name);
            }
        }
    }
