import java.net.*;

public class MyDecorator {
    private final Map<String, Function> urlFunctionMap;

    public MyDecorator() {
        this.urlFunctionMap = new HashMap<>();
    }

    public void addUrl(String url, Function function) {
        this.urlFunctionMap.put(url, function);
    }

    public String getResponseForURL(String url) {
        return this.urlFunctionMap.get(url).apply();
    }
}