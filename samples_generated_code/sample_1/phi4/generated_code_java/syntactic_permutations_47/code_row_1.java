import java.util.HashMap;
import java.util.Map;

interface HttpHandler {
    void handleRequest(String url);
}

class BaseHttpHandler implements HttpHandler {
    @Override
    public void handleRequest(String url) {
        System.out.println("Handling request for URL: " + url);
    }
}

abstract class UrlDecorator implements HttpHandler {
    protected HttpHandler decoratedHandler;

    public UrlDecorator(HttpHandler decoratedHandler) {
        this.decoratedHandler = decoratedHandler;
    }

    @Override
    public void handleRequest(String url) {
        if (shouldHandle(url)) {
            handle(url);
        } else {
            decoratedHandler.handleRequest(url);
        }
    }

    protected abstract boolean shouldHandle(String url);

    protected abstract void handle(String url);
}

class SpecificUrlHandler extends UrlDecorator {

    private final String targetUrl;

    public SpecificUrlHandler(HttpHandler decoratedHandler, String targetUrl) {
        super(decoratedHandler);
        this.targetUrl = targetUrl;
    }

    @Override
    protected boolean shouldHandle(String url) {
        return url.equals(targetUrl);
    }

    @Override
    protected void handle(String url) {
        System.out.println("Specific handler for URL: " + url + ". Custom processing logic.");
    }
}

public class Main {
    public static void main(String[] args) {
        HttpHandler baseHandler = new BaseHttpHandler();
        HttpHandler specificUrlHandler = new SpecificUrlHandler(baseHandler, "/specific-url");

        // Test with different URLs
        String[] testUrls = {"/home", "/about", "/specific-url", "/contact"};

        for (String url : testUrls) {
            specificUrlHandler.handleRequest(url);
        }
    }
}