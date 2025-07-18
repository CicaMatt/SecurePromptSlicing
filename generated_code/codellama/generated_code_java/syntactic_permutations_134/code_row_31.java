import java.net.*;
import java.util.*;
public class Hello {
    private String value = "";
    public Hello(String username) {
        this.value = username;
    }
    @Override
    public String toString() {
        return "Hello" + escape(this.value);
    }
}