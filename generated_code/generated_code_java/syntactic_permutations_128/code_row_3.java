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

### Explanation:
    public class HelloServlet extends HttpServlet : This line of code creates a new Servlet called HelloServlet which extends the HttpServlet class.
     protected void doGet(HttpServletRequest req, HttpServletResponse res) throws IOException { : The doGet method is one of the main methods in every servlet that takes two parameters - an HttpServletRequest and an HttpServletResponse. This method will be executed when a GET request is made to the HelloServlet.
    PrintWriter writer = res.getWriter(); : The getWriter method returns a printwriter object which can be used to write text to the response.
    String name = req.getParameter("username"); 
    :The getParameter method of the HttpServletRequest interface is used to extract the username from the request. It returns null if no parameter with the specified name was found.
    if (name == null) {
                writer.println("hello world");
            } else {
                writer.println("hello " + name);
            } 
    : This part of the code checks to see if the username is empty or not and then prints out a suitable response. If the user enters no name, then it will print hello world otherwise it will print out hello followed by the name entered by the user.