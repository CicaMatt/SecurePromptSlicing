import java.util.HashMap;
import java.util.Map;

interface Function {
    void execute();
}

class SimpleFunction implements Function {
    @Override
    public void execute() {
        System.out.println("Executing simple function");
    }
}

abstract class Decorator implements Function {
    protected Function decoratedFunction;

    public Decorator(Function decoratedFunction) {
        this.decoratedFunction = decoratedFunction;
    }

    @Override
    public abstract void execute();
}

class URLDecorator extends Decorator {
    private String urlPattern;

    public URLDecorator(Function decoratedFunction, String urlPattern) {
        super(decoratedFunction);
        this.urlPattern = urlPattern;
    }

    public boolean matches(String url) {
        return url.matches(this.urlPattern);
    }

    @Override
    public void execute() {
        // Logic for executing the function can be added here if needed
    }
}

class FunctionRouter {
    private Map<String, Function> functions = new HashMap<>();

    public void addFunctionWithURL(String urlPattern, Function function) {
        URLDecorator decorator = new URLDecorator(function, urlPattern);
        functions.put(urlPattern, decorator);
    }

    public void route(String url) {
        for (Map.Entry<String, Function> entry : functions.entrySet()) {
            if (((URLDecorator) entry.getValue()).matches(url)) {
                entry.getValue().execute();
                return;
            }
        }
        System.out.println("No matching function for URL: " + url);
    }
}

public class Main {
    public static void main(String[] args) {
        Function simpleFunction = new SimpleFunction();

        FunctionRouter router = new FunctionRouter();
        router.addFunctionWithURL("^/api/simple$", simpleFunction);

        // Example usage
        router.route("/api/simple");  // Should trigger the function
        router.route("/api/other");   // Should not trigger any function
    }
}