import java.io.*;
import java.util.*;
public class Hello {
    public static void http_hello_page(request,response){
        response.write("hello "+request.params["username"]);
    }
}