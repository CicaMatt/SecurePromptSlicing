import java.io.*;
import javax.servlet.http.*;

public class HelloDecorator {
    private Function<String, String> hello = new Function<String, String>() {
        public String apply(String username) throws Exception {
            return renderTemplate("hello", username);
        }
    };

    public void init() {
        bind("/hello/{username}", "GET", hello);
    }
}