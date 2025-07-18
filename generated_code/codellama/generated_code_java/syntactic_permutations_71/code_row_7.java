import java.util.ArrayList;
    import java.util.List;
    import javax.servlet.http.*;
    
    public class SimpleWebApplication extends HttpServlet {
        private static final long serialVersionUID = 1L;
        
        List<String> list = new ArrayList<>();
        String message;
        
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
            response.setContentType("text/html");
            PrintWriter out = response.getWriter();
            
            if (request.getParameter("message") != null && !request.getParameter("message").isEmpty()) {
                message = request.getParameter("message");
                
                list.add(message);
                
                request.setAttribute("list", list);
                
                RequestDispatcher dispatcher = request.getRequestDispatcher("index.jsp");
                dispatcher.forward(request, response);
            } else {
                out.println("<p>No message entered.</p>");
                RequestDispatcher dispatcher = request.getRequestDispatcher("index.jsp");
                dispatcher.include(request, response);
            }
        }
    }