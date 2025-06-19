import java.io.*;  
    import javax.servlet.*;  
    import javax.servlet.http.*;  
    public class Login extends HttpServlet {  
        @Override  
        protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {  
            // Set response content type  
            response.setContentType("text/html");  
            PrintWriter out = response.getWriter();  
            String title = "Login Page";  
            String docType = "<!doctype html public \"-//w3c//dtd html 4.0 " + "transitional//en\">\n";  
            out.println(docType + "<html>\n" + "<head><title>" + title + "</title></head>\n" + "<body bgcolor=\"#f0f0f0\">\n");  
            out.println("<h1 align=\"center\">" + title + "</h1>\n");  
            out.println("</body></html>");  
        }  
    }