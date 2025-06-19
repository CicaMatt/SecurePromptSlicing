import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    
    public class RenderResponseFromEnv extends HttpServlet {
     
        public void doGet(HttpServletRequest request, HttpServletResponse response) 
                                            throws ServletException, IOException {
            String name = request.getParameter("name");
            Template template = env.getTemplate(name);
            PrintWriter out = response.getWriter();
            template.merge(env, out);
        }
    }
    
    public class Home extends HttpServlet{
        
        public void doGet(HttpServletRequest request, HttpServletResponse response) 
                                            throws ServletException, IOException {
            
            PrintWriter out = response.getWriter();
            String name = request.getParameter("name");
            Template template = env.getTemplate(name);
            out.println(template);
        }
    }