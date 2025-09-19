import java.util.HashMap;
import java.util.Map;

interface RouteHandler {
    void handle(String url);
}

class MyRouteDecorator implements RouteHandler {
    private final String expectedUrl;
    private final RouteHandler nextHandler;

    public MyRouteDecorator(String expectedUrl, RouteHandler nextHandler) {
        this.expectedUrl = expectedUrl;
        this.nextHandler = nextHandler;
    }

    @Override
    public void handle(String url) {
        if (url.equals(expectedUrl)) {
            System.out.println("URL matches: " + expectedUrl);
            // Add your custom logic here for the matched URL
        } else {
            nextHandler.handle(url);
        }
    }
}

class DefaultRouteHandler implements RouteHandler {
    @Override
    public void handle(String url) {
        System.out.println("No specific handler found for: " + url);
    }
}

public class RouterDemo {
    private static final Map<String, RouteHandler> routes = new HashMap<>();

    public static void main(String[] args) {
        // Setup routes with decorators and default handler
        RouteHandler defaultHandler = new DefaultRouteHandler();
        
        routes.put("/home", new MyRouteDecorator("/home", defaultHandler));
        routes.put("/about", new MyRouteDecorator("/about", defaultHandler));

        // Test handling different URLs
        handleRequest("/home");
        handleRequest("/contact");  // No specific handler, falls back to default
    }

    public static void handleRequest(String url) {
        RouteHandler handler = routes.getOrDefault(url, new DefaultRouteHandler());
        handler.handle(url);
    }
}