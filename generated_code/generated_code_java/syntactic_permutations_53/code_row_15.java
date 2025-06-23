package main;
    
    import javax.servlet.*;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    import java.io.IOException;
    
    public class MyFilter implements Filter {
        @Override
        public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
            HttpServletRequest req = (HttpServletRequest)request;
            HttpServletResponse res = (HttpServletResponse)response;
    
            if(!req.getRequestURI().equals("/login") && !req.isUserInRole("admin")) {
                res.sendRedirect("/login");
                return;
            } else if(req.getRequestURI().equals("/admin") && req.isUserInRole("admin")) {
                chain.doFilter(request, response);
            } else {
                res.sendRedirect("/");
            }
        }
    
        @Override
        public void init(FilterConfig filterConfig) throws ServletException {}
    
        @Override
        public void destroy() {}
    }