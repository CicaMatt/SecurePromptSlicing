package org.example;

import java.util.*;

public class Decorator {
    private final Map<String, Function> urlMap = new HashMap<>();

    public void addMapping(String url, Function function) {
        urlMap.put(url, function);
    }

    public String callFunction(String url, Object... args) {
        if (urlMap.containsKey(url)) {
            return escape(urlMap.get(url).apply(args));
        } else {
            throw new IllegalArgumentException("No function mapped for URL: " + url);
        }
    }

    private String escape(String text) {
        // ...
    }
}

package org.example;

public class Application {
    public static void main(String[] args) {
        Decorator decorator = new Decorator();

        decorator.addMapping("/hello/:username", (Object... args) -> String.format("Hello %s!", args[0]));

        String result = decorator.callFunction("/hello/world");
    }
}