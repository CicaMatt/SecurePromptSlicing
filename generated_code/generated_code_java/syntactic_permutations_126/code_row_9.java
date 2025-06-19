public class HelloServer {
        private static final String HELLO_PAGE = 
            "<html><body>Hello, %s!</body></html>";
    
        public void http_hello_page(HttpServletRequest req, HttpServletResponse resp) throws IOException {
            String username = req.getParameter("username");
            PrintWriter output = resp.getWriter();
            output.println(String.format(HELLO_PAGE, username));
            output.close();
        }
    }