import java.util.Map;
import javax.servlet.http.HttpServletRequest;

public class WebApplication {

    public static void main(String[] args) {
        // Example usage
        Map<String, String> env = Map.of("template", "Hello, {{name}}!");
        HttpServletRequest request = new MockHttpServletRequest();
        request.setParameter("name", "World");
        
        String response = home(request, env);
        System.out.println(response);  // Output: Hello, World!
    }

    public static String home(HttpServletRequest request, Map<String, String> env) {
        return renderResponseFromEnv(env, request);
    }

    public static String renderResponseFromEnv(Map<String, String> env, HttpServletRequest request) {
        String name = request.getParameter("name");
        String template = env.get("template");

        if (template != null && name != null) {
            return template.replace("{{name}}", name);
        } else {
            return "Error: Template or Name not found.";
        }
    }

    // Mock HttpServletRequest for demonstration purposes
    static class MockHttpServletRequest implements HttpServletRequest {
        private final Map<String, String> parameters = Map.of("name", "World");

        @Override
        public String getParameter(String name) {
            return parameters.get(name);
        }

        // Implement other methods with empty bodies or default behavior
        @Override
        public javax.servlet.ServletContext getServletContext() { return null; }
        @Override
        public javax.servlet.http.HttpServletRequestWrapper getRequest() { return null; }
        @Override
        public java.util.Enumeration<String> getParameterNames() { return null; }
        @Override
        public String[] getParameterValues(String name) { return new String[0]; }
        @Override
        public String getMethod() { return null; }
        @Override
        public javax.servlet.http.Part getPart(String name) { return null; }
        @Override
        public java.util.Collection<javax.servlet.http.Part> getParts() { return null; }
        @Override
        public String getAttribute(String name) { return null; }
        @Override
        public javax.servlet.http.HttpServletRequest getRequest() { return this; }
        @Override
        public void setAttribute(String name, Object o) {}
        @Override
        public Object removeAttribute(String name) { return null; }
        @Override
        public java.util.Enumeration<String> getAttributeNames() { return null; }
        @Override
        public String getRequestedSessionId() { return null; }
        @Override
        public boolean isRequestedSessionIdValid() { return false; }
        @Override
        public boolean isRequestedSessionIdFromCookie() { return false; }
        @Override
        public boolean isRequestedSessionIdFromURL() { return false; }
        @Override
        public boolean isRequestedSessionIdFromUrl() { return false; }
        @Override
        public String getAuthType() { return null; }
        @Override
        public java.security.Principal getUserPrincipal() { return null; }
        @Override
        public String getRemoteUser() { return null; }
        @Override
        public boolean isUserInRole(String role) { return false; }
        @Override
        public javax.servlet.http.HttpSession getSession(boolean create) { return null; }
        @Override
        public javax.servlet.http.HttpSession getSession() { return null; }
        @Override
        public java.util.Collection<java.security.Principal> getUserPrincipals() { return null; }
        @Override
        public String getRequestURI() { return null; }
        @Override
        public StringBuffer getRequestURL() { return null; }
        @Override
        public String getServletPath() { return null; }
        @Override
        public String getPathInfo() { return null; }
        @Override
        public String getPathTranslated() { return null; }
        @Override
        public String getContextPath() { return null; }
        @Override
        public String getQueryString() { return null; }
        @Override
        public String getRemoteAddr() { return null; }
        @Override
        public String getRemoteHost() { return null; }
        @Override
        public void setAttribute(String name, Object o) {}
        @Override
        public Object getAttribute(String name) { return null; }
        @Override
        public Enumeration<String> getHeaderNames() { return null; }
        @Override
        public String getHeader(String name) { return null; }
        @Override
        public Enumeration<String> getHeaders(String name) { return null; }
        @Override
        public String getMethod() { return null; }
        @Override
        public boolean isSecure() { return false; }
        @Override
        public javax.servlet.http.Cookie[] getCookies() { return new javax.servlet.http.Cookie[0]; }
        @Override
        public long getDateHeader(String name) { return 0L; }
        @Override
        public int getIntHeader(String name) { return 0; }
        @Override
        public String getHeader(String name) { return null; }
        @Override
        public String getRealPath(String path) { return null; }
        @Override
        public boolean isUserRequestedSessionCreation() { return false; }
    }
}