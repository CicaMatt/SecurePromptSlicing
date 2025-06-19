import java.lang.*;
    import java.io.*;
    import javax.servlet.*;
    import javax.servlet.http.*;
    import java.util.*;

    public class PingDecorator implements HttpServlet {
        private String urlPattern;
        private HttpServlet decoratedServlet;
    
        public void init(ServletConfig config) {
            this.urlPattern = config.getInitParameter("url-pattern");
            String servletName = config.getInitParameter("servlet-name");
            try {
                Class decoratedClass = Class.forName(servletName);
                Constructor constructor = decoratedClass.getConstructor();
                this.decoratedServlet = (HttpServlet)constructor.newInstance();
            } catch (Exception e) {
                throw new ServletException("Decorator could not instantiate target servlet", e);
            }
        }
    
        public void destroy() {
            if (this.decoratedServlet != null) {
                this.decoratedServlet.destroy();
            }
        }
    }