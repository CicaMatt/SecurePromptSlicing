import java.util.HashMap;
import java.util.Map;

interface HttpHandler {
    void handleRequest(String url);
}

class BaseHandler implements HttpHandler {

    @Override
    public void handleRequest(String url) {
        System.out.println("Handling request for URL: " + url);
    }
}

abstract class Decorator implements HttpHandler {
    protected HttpHandler decoratedHandler;

    public Decorator(HttpHandler decoratedHandler) {
        this.decoratedHandler = decoratedHandler;
    }

    @Override
    public void handleRequest(String url) {
        decoratedHandler.handleRequest(url);
    }
}

class UrlBasedHandlerDecorator extends Decorator {

    private final Map<String, Runnable> urlHandlers;

    public UrlBasedHandlerDecorator(HttpHandler decoratedHandler) {
        super(decoratedHandler);
        this.urlHandlers = new HashMap<>();
    }

    public void addUrlHandler(String urlPattern, Runnable handlerAction) {
        urlHandlers.put(urlPattern, handlerAction);
    }

    @Override
    public void handleRequest(String url) {
        for (Map.Entry<String, Runnable> entry : urlHandlers.entrySet()) {
            if (url.matches(entry.getKey())) {
                entry.getValue().run();
                return;
            }
        }
        super.handleRequest(url); // Fallback to base handler if no match found
    }
}

public class Main {

    public static void main(String[] args) {
        HttpHandler baseHandler = new BaseHandler();

        UrlBasedHandlerDecorator decoratedHandler =
                new UrlBasedHandlerDecorator(baseHandler);

        decoratedHandler.addUrlHandler("^/api/users$", () -> System.out.println("User API endpoint hit"));
        decoratedHandler.addUrlHandler("^/api/products$", () -> System.out.println("Product API endpoint hit"));

        // Test the handler with different URLs
        decoratedHandler.handleRequest("/api/users");
        decoratedHandler.handleRequest("/api/products");
        decoratedHandler.handleRequest("/unknown/path");
    }
}