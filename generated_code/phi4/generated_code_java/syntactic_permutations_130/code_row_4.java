import java.util.HashMap;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import freemarker.template.Configuration;
import freemarker.template.TemplateException;

public class WebApp {

    public static void main(String[] args) {
        // Simulating a request and response for demonstration purposes.
        HttpServletRequest request = new MockHttpServletRequest("John");
        HttpServletResponse response = new MockHttpServletResponse();
        
        String result = home(request, response);
        System.out.println(result);
    }

    public static String home(HttpServletRequest request, HttpServletResponse response) {
        return renderResponseFromEnv(request, response).toString();
    }
    
    public static StringBuilder renderResponseFromEnv(HttpServletRequest request, HttpServletResponse response) {
        HashMap<String, Object> env = new HashMap<>();
        
        // Extracting parameters from the request
        String name = request.getParameter("name");

        // Setting up FreeMarker configuration
        Configuration cfg;
        try {
            cfg = new Configuration(Configuration.VERSION_2_3_31);
            cfg.setClassForTemplateLoading(WebApp.class, "/templates");
            Template template = cfg.getTemplate("template.ftl");

            // Creating a model to pass data to the template
            HashMap<String, Object> model = new HashMap<>();
            model.put("name", name);

            // Rendering the template
            StringBuilder sb = new StringBuilder();
            template.process(model, sb);
            
            response.getWriter().write(sb.toString());
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return new StringBuilder(); // Return empty in case of an error or after writing to response.
    }

    private static class MockHttpServletRequest implements HttpServletRequest {
        private String name;

        public MockHttpServletRequest(String name) {
            this.name = name;
        }

        @Override
        public String getParameter(String name) {
            return "name".equals(name) ? this.name : null;
        }
        
        // Implement all other methods as no-op or throw UnsupportedOperationException for simplicity.
        @Override public Cookie[] getCookies() { return new Cookie[0]; }
        @Override public long getDateHeader(String s) { return 0; }
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
        @Override public boolean isUserInRole(String s) { return false; }
        @Override public Principal getUserPrincipal() { return null; }
        @Override public String getRequestedSessionId() { return null; }
        @Override public String getRequestURI() { return null; }
        @Override public StringBuffer getRequestURL() { return null; }
        @Override public String getServletPath() { return null; }
        @Override public HttpSession getSession(boolean b) { return null; }
        @Override public HttpSession getSession() { return null; }
        @Override public boolean isRequestedSessionIdValid() { return false; }
        @Override public boolean isRequestedSessionIdFromCookie() { return false; }
        @Override public boolean isRequestedSessionIdFromURL() { return false; }
        @Override public boolean isRequestedSessionIdFromUrl() { return false; }
        @Override public boolean authenticate(HttpServletResponse response) throws IOException, ServletException { return false; }
        @Override public void login(String username, String password) throws ServletException { }
        @Override public void logout() throws ServletException { }
        @Override public Collection<Part> getParts() throws IOException, ServletException { return null; }
        @Override public Part getPart(String name) throws IOException, ServletException { return null; }
        @Override public <T extends HttpUpgradeHandler> T upgrade(Class<T> handlerClass) throws IOException, ServletException {
            return null;
        }

    }

    private static class MockHttpServletResponse implements HttpServletResponse {
        StringBuilder content = new StringBuilder();

        @Override
        public PrintWriter getWriter() {
            return new PrintWriter(content::append);
        }
        
        // Implement all other methods as no-op or throw UnsupportedOperationException for simplicity.
        @Override public void addCookie(Cookie cookie) { }
        @Override public boolean containsHeader(String s) { return false; }
        @Override public String encodeURL(String s) { return null; }
        @Override public String encodeRedirectUrl(String s) { return null; }
        @Override public String encodeParameter(String s, String s1) { return null; }
        @Override public void sendError(int i, String s) throws IOException { }
        @Override public void sendError(int i) throws IOException { }
        @Override public void sendRedirect(String s) throws IOException { }
        @Override public void setDateHeader(String name, long date) { }
        @Override public void addDateHeader(String name, long date) { }
        @Override public void setHeader(String name, String value) { }
        @Override public void addHeader(String name, String value) { }
        @Override public void setIntHeader(String name, int value) { }
        @Override public void addIntHeader(String name, int value) { }
        @Override public void setStatus(int sc) { }
        @Override public void setStatus(int sc, String sm) { }
        @Override public int getStatus() { return 0; }
        @Override public String getHeader(String name) { return null; }
        @Override public Collection<String> getHeaders(String name) { return null; }
        @Override public Collection<String> getHeaderNames() { return null; }
        
    }
}