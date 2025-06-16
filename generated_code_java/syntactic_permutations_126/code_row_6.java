import java.io.*;
    import javax.servlet.*;
    
    public class HelloWorld extends GenericServlet {
        
        private static final long serialVersionUID = 1L;
    
        @Override
        public void service(ServletRequest request, ServletResponse response)
                        throws ServletException, IOException {
            String username = request.getParameter("username");
            PrintWriter output = response.getWriter();
            String outputbuf = "";
            
            if (username == null) {
                outputbuf += "<p>You did not enter a name</p>";
            } else {
                outputbuf += "<p>Hello, " + username + "</p>";
            }
            
            output.println(outputbuf);
            output.close();
        }
    }