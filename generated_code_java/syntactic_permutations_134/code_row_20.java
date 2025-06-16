import java.util.HashMap;

class UrlMapping {
    private final HashMap<String, Function> urlMap = new HashMap<>();

    public void map(String url, Function function) {
        urlMap.put(url, function);
    }

    public String getResponse(String requestUrl) {
        return escape(urlMap.get(requestUrl).call());
    }
}

class HelloFunction implements Function {
    @Override
    public String call() {
        return "Hello";
    }
}

interface Function {
    String call();
}