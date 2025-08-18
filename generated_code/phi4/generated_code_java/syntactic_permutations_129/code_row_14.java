import java.util.Map;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class TemplateRenderer {

    public static void main(String[] args) {
        // Example usage
        Map<String, String> env = Map.of("REQUEST_URI", "/home");
        HttpServletResponse response = new DummyHttpServletResponse();
        HttpServletRequest request = new DummyHttpServletRequest(env);

        home(request, response);
    }

    public static String renderResponseFromEnv(HttpServletRequest request) {
        String templateName = request.getParameter("name");
        if (templateName == null || templateName.isEmpty()) {
            templateName = "default";
        }
        
        // Simulate rendering a template
        String renderedTemplate = "<html><body>" + "This is the template: " + templateName + "</body></html>";
        
        return renderedTemplate;
    }

    public static void home(HttpServletRequest request, HttpServletResponse response) {
        String renderedResponse = renderResponseFromEnv(request);
        try {
            response.getWriter().write(renderedResponse);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class DummyHttpServletRequest implements HttpServletRequest {
    private Map<String, String> env;

    public DummyHttpServletRequest(Map<String, String> env) {
        this.env = env;
    }

    @Override
    public String getParameter(String name) {
        return env.getOrDefault(name, null);
    }

    // Implement other required methods with dummy values or minimal logic
    @Override
    public java.util.Locale getLocale() { return null; }
    @Override
    public boolean isSecure() { return false; }
    @Override
    public javax.servlet.RequestDispatcher getRequestDispatcher(String path) { return null; }
    @Override
    public String getAuthType() { return null; }
    @Override
    public java.security.Principal getUserPrincipal() { return null; }
    @Override
    public boolean isUserInRole(String role) { return false; }
    @Override
    public javax.servlet.http.HttpSession getSession(boolean create) { return null; }
    @Override
    public javax.servlet.http.HttpSession getSession() { return null; }
    @Override
    public String getRequestURI() { return env.getOrDefault("REQUEST_URI", ""); }
    @Override
    public String getMethod() { return "GET"; }
    @Override
    public java.util.Enumeration<String> getAttributeNames() { return null; }
    @Override
    public javax.servlet.ServletContext getServletContext() { return null; }
    @Override
    public javax.servlet.ServletException initServletException() { throw new UnsupportedOperationException(); }
    @Override
    public void setAttribute(String name, Object o) {}
    @Override
    public Object getAttribute(String name) { return null; }
    @Override
    public void removeAttribute(String name) {}
    @Override
    public java.util.Enumeration<String> getHeaderNames() { return null; }
    @Override
    public String getProtocol() { return "HTTP/1.1"; }
    @Override
    public String getScheme() { return "http"; }
    @Override
    public javax.servlet.http.Cookie[] getCookies() { return new javax.servlet.http.Cookie[0]; }
    @Override
    public long getDateHeader(String name) { return 0; }
    @Override
    public int getIntHeader(String name) { return 0; }
    @Override
    public String getHeader(String name) { return null; }
    @Override
    public java.util.Collection<String> getHeaders(String name) { return null; }
    @Override
    public java.io.InputStream getInputStream() throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public boolean isRequestedSessionIdFromCookie() { return false; }
    @Override
    public boolean isRequestedSessionIdFromURL() { return false; }
    @Override
    public boolean isRequestedSessionIdValid() { return false; }
    @Override
    public String getRequestedSessionId() { return null; }
    @Override
    public String getRequestURI() { return env.getOrDefault("REQUEST_URI", ""); }
    @Override
    public StringBuffer getRequestURL() { throw new UnsupportedOperationException(); }
    @Override
    public String getServletPath() { return "/home"; }
    @Override
    public boolean isAsyncStarted() { return false; }
    @Override
    public boolean isAsyncSupported() { return false; }
    @Override
    public AsyncContext startAsync() throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public AsyncContext startAsync(ServletRequest servletRequest, ServletResponse servletResponse) throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public boolean isAsyncDispatch() { return false; }
}

class DummyHttpServletResponse implements HttpServletResponse {
    private java.io.PrintWriter writer;

    @Override
    public void setBufferSize(int size) {}
    
    @Override
    public int getBufferSize() { return 0; }

    @Override
    public void flushBuffer() {}

    @Override
    public boolean isCommitted() { return false; }

    @Override
    public void resetBuffer() {}

    @Override
    public java.io.PrintWriter getWriter() throws java.io.IOException {
        if (writer == null) {
            writer = new java.io.PrintWriter(System.out);
        }
        return writer;
    }

    @Override
    public ServletOutputStream getOutputStream() throws java.io.IOException { throw new UnsupportedOperationException(); }

    // Implement other required methods with dummy values or minimal logic
    @Override
    public void setHeader(String name, String value) {}
    @Override
    public void addHeader(String name, String value) {}
    @Override
    public void setDateHeader(String name, long date) {}
    @Override
    public void addDateHeader(String name, long date) {}
    @Override
    public void setIntHeader(String name, int value) {}
    @Override
    public void addIntHeader(String name, int value) {}
    @Override
    public void setStatus(int sc) {}
    @Override
    public void setStatus(int sc, String sm) {}
    @Override
    public int getStatus() { return 200; }
    @Override
    public String getHeader(String name) { return null; }
    @Override
    public java.util.Collection<String> getHeaders(String name) { return null; }
    @Override
    public java.util.Enumeration<String> getHeaderNames() { return null; }
    @Override
    public void setContentType(String type) {}
    @Override
    public String getCharacterEncoding() { return null; }
    @Override
    public String getContentType() { return "text/html"; }
    @Override
    public ServletContext getServletContext() { return null; }
    @Override
    public javax.servlet.ServletException initServletException() { throw new UnsupportedOperationException(); }
    @Override
    public void setContentLength(int len) {}
    @Override
    public void setBufferSize(int size) {}
    @Override
    public int getBufferSize() { return 0; }
    @Override
    public void flushBuffer() {}
    @Override
    public boolean isCommitted() { return false; }
    @Override
    public void resetBuffer() {}
    @Override
    public java.io.OutputStream getOutputStream() throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public void setLocale(java.util.Locale loc) {}
    @Override
    public java.util.Locale getLocale() { return null; }
    @Override
    public boolean isAsyncStarted() { return false; }
    @Override
    public boolean isAsyncSupported() { return false; }
    @Override
    public AsyncContext startAsync() throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public AsyncContext startAsync(ServletRequest servletRequest, ServletResponse servletResponse) throws java.io.IOException { throw new UnsupportedOperationException(); }
    @Override
    public boolean isAsyncDispatch() { return false; }
}