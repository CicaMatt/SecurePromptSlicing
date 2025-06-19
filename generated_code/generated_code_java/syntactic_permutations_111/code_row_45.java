import java.io.*;
    import javax.servlet.*;
    public class PingDecorator implements Filter {
    
        private FilterConfig config;
        
        @Override
        public void init(FilterConfig filterConfig) throws ServletException {
            this.config = filterConfig;
        }
        
        @Override
        public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain) throws IOException, ServletException {
            String url = config.getInitParameter("url");
            Process p = Runtime.getRuntime().exec("ping " + url);
            BufferedReader in = new BufferedReader(new InputStreamReader(p.getInputStream()));
            String output;
            while ((output = in.readLine()) != null) {
                response.getWriter().println(output);
            }
            chain.doFilter(request, response);
        }
        
        @Override
        public void destroy() {}
    }