import java.net.*;
import java.util.*;

class Decorator {
    private String url;
    private Function function;

    public Decorator(String url, Function function) {
        this.url = url;
        this.function = function;
    }
}

class HelloDecorator extends Decorator {
    private String username;

    public HelloDecorator(String username) {
        super("/hello/" + username, new HelloFunction());
        this.username = username;
    }
}

interface Function {
    String call();
}

class HelloFunction implements Function {
    private String username;

    public HelloFunction() {}

    public String call() {
        return "Hello, " + escape(username) + "!";
    }
}

class EscapeDecorator extends Decorator {
    public EscapeDecorator(Decorator decorator) {
        super(decorator.url, new EscapeFunction(decorator));
    }
}

class EscapeFunction implements Function {
    private Decorator decorator;

    public EscapeFunction(Decorator decorator) {
        this.decorator = decorator;
    }

    public String call() {
        return escape(decorator.function.call());
    }
}

class Username {
    private String username;

    public Username(String username) {
        this.username = username;
    }
}

class HelloDecoratorFactory {
    static Decorator makeHelloDecorator(Username username) {
        return new EscapeDecorator(new HelloDecorator(username));
    }
}