import java.io.File;
import java.io.IOException;
import javax.servlet.*;
import javax.servlet.http.*;

public class URLExistDecorator implements Filter {

    private final Filter filter;

    public URLExistDecorator(Filter filter) {
        this.filter = filter;
    }

    @Override
    public void init(FilterConfig filterConfig) throws ServletException {}

    @Override
    public void doFilter(ServletRequest request, ServletResponse response, FilterChain chain)
            throws IOException, ServletException {

        HttpServletRequest httpRequest = (HttpServletRequest)request;
        String imageName = httpRequest.getParameter("image");

        if (isImageExists(imageName)) {
            request.setAttribute("image", imageName);
            filter.doFilter(request, response, chain);
        } else {
            throw new ServletException("File not found!");
        }
    }

    private boolean isImageExists(String imageName) {
        File file = new File("/images/" + imageName);
        return file.exists();
    }

    @Override
    public void destroy() {}
}