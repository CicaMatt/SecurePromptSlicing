package com.example;
    
    import java.io.IOException;
    import javax.servlet.Filter;
    import javax.servlet.FilterChain;
    import javax.servlet.FilterConfig;
    import javax.servlet.ServletException;
    import javax.servlet.ServletRequest;
    import javax.servlet.ServletResponse;
    import javax.servlet.http.HttpServletRequest;
    import javax.servlet.http.HttpServletResponse;
    
    public class RedirectFilter implements Filter {
        private static final String REGEX_PATTERN = ".*example\\.com.*";
    
        @Override
        public void init(FilterConfig filterConfig) throws ServletException {}
    
        @Override
        public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
            HttpServletRequest httpRequest = (HttpServletRequest)request;
            HttpServletResponse httpResponse = (HttpServletResponse)response;
            String target = httpRequest.getParameter("target");
    
            if (target != null && target.matches(REGEX_PATTERN)) {
                httpResponse.sendRedirect(target);
            } else {
                httpResponse.sendRedirect("/");
            }
        }
    
        @Override
        public void destroy() {}
    }