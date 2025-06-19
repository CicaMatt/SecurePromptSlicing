import java.util.HashMap;<br>
public class Decorator {<br>
    public static HashMap&lt;String, String&gt; map = new HashMap&lt;&gt;();<br>
    public void hello(String username) {<br>
        return "Hello" + escape(username);<br>
    }<br>
}<br>