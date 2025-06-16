import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class MainPage extends HttpServlet {
        public void doGet(HttpServletRequest request, HttpServletResponse response)
                throws ServletException, IOException {
            response.setContentType("text/html;charset=UTF-8");
            PrintWriter out = response.getWriter();
            out.println("<!DOCTYPE html>");
            out.println("<html>");
            out.println("<head>");
            out.println("<title>Chat Room</title>");            
            out.println("</head>");
            out.println("<body>");
            out.println("<h1>Welcome to the Chat Room!</h1>");
            out.println("<form action=\"/post\" method=\"POST\">");
            out.println("<input type=\"text\" name=\"username\">");
            out.println("<br>");
            out.println("<input type=\"text\" name=\"message\">");
            out.println("<br>");
            out.println("<button type=\"submit\">Send</button>");
            out.println("</form>");
            out.println("</body>");
            out.println("</html>");   
        }
    }