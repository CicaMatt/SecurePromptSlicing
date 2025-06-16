import java.io.*;
import java.lang.reflect.InvocationTargetException;

public class PingDecorator implements Function<String, String> {
    private Function<String, String> decoratedFunction;
    private String url;
    public PingDecorator(Function<String, String> decoratedFunction) {
        this.decoratedFunction = decoratedFunction;
    }

    @Override
    public String apply(String input) throws InvocationTargetException {
        if (input == null || !input.equals("ping")){
            return "Invalid Input";
        }
        String result = this.decoratedFunction.apply(this.url);
        if (result == null){
            throw new RuntimeException();
        }
        return result;
    }
}