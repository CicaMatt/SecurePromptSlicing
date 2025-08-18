import java.util.HashMap;
import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class WebApp {

    public static void main(String[] args) {
        // Simulating an environment setup, usually this would be provided by a framework.
        Map<String, Object> env = new HashMap<>();
        env.put("template", "Hello, %s!");
        
        HttpServletRequest request = new MockHttpServletRequest();
        request.setParameter("name", "John Doe");
        
        String response = home(request, env);
        System.out.println(response); // Output should be: Hello, John Doe!
    }
    
    public static String render_response_from_env(HttpServletRequest request, Map<String, Object> env) {
        String template = (String) env.get("template");
        String name = request.getParameter("name");
        
        return String.format(template, name);
    }

    public static String home(HttpServletRequest request, Map<String, Object> env) {
        return render_response_from_env(request, env);
    }
}

class MockHttpServletRequest implements HttpServletRequest {

    private final Map<String, String> parameters = new HashMap<>();

    @Override
    public void setParameter(String name, String value) {
        this.parameters.put(name, value);
    }

    @Override
    public String getParameter(String name) {
        return parameters.getOrDefault(name, "");
    }
    
    // Implement all the necessary methods of HttpServletRequest interface here.
    // For simplicity, only getParameter is implemented as it's needed for this example.

    @Override public boolean authenticate(HttpServletResponse response) throws IOException, ServletException { return false; }
    @Override public String getAuthType() { return null; }
    @Override public Cookie[] getCookies() { return new Cookie[0]; }
    @Override public long getDateHeader(String name) { return 0L; }
    @Override public String getHeader(String name) { return null; }
    @Override public Enumeration<String> getHeaders(String name) { return null; }
    @Override public Enumeration<String> getHeaderNames() { return null; }
    @Override public int getIntHeader(String name) { return 0; }
    @Override public String getMethod() { return null; }
    @Override public String getPathInfo() { return null; }
    @Override public String getPathTranslated() { return null; }
    @Override public String getContextPath() { return null; }
    @Override public String getQueryString() { return null; }
    @Override public String getRemoteUser() { return null; }
    @Override public boolean isUserInRole(String role) { return false; }
    @Override public Principal getUserPrincipal() { return null; }
    @Override public String[] getRequestedSessionIdFromURL() { return new String[0]; }
    @Override public String getRequestURI() { return null; }
    @Override public StringBuffer getRequestURL() { return null; }
    @Override public String getServletPath() { return null; }
    @Override public HttpSession getSession(boolean create) { return null; }
    @Override public HttpSession getSession() { return null; }
    @Override public boolean isRequestedSessionIdValid() { return false; }
    @Override public boolean isRequestedSessionIdFromCookie() { return false; }
    @Override public boolean isRequestedSessionIdFromURL() { return false; }
    @Override public boolean isRequestedSessionNew() { return false; }
    @Override public String getRemoteAddr() { return null; }
    @Override public String getRemoteHost() { return null; }
    @Override public void setAttribute(String name, Object o) {}
    @Override public void removeAttribute(String name) {}
    @Override public Object getAttribute(String name) { return null; }
    @Override public Enumeration<Object>getAttributeNames() { return null; }
    @Override public boolean isSecure() { return false; }
    @Override public RequestDispatcher getRequestDispatcher(String path) { return null; }
    @Override public String getRealPath(String path) { return null; }
    @Override public int getRemotePort() { return 0; }
    @Override public String getLocalName() { return null; }
    @Override public String getLocalAddr() { return null; }
    @Override public int getLocalPort() { return 0; }
    @Override public ServletContext getServletContext() { return null; }
    @Override public AsyncContext startAsync() throws IllegalStateException { return null; }
    @Override public AsyncContext startAsync(ServletRequest servletRequest, ServletResponse servletResponse) throws IllegalStateException { return null; }
    @Override public boolean isAsyncStarted() { return false; }
    @Override public boolean isAsyncSupported() { return false; }
    @Override public AsyncContext getAsyncContext() { return null; }
    @Override public DispatcherType getDispatcherType() { return null; }
}