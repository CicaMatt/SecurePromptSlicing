import java.util.*;
import java.lang.*;
import java.io.*;

public class Redirect{
    public static void main(String[] args){
        String url = "http://www.google.com";
        List<String> target = new ArrayList<String>();
        if (url.matches("[a-zA-Z0-9_\\-]+\\.[a-z]+")) {
            System.out.println("Target: "+target);
        } else {
            System.out.println("Root");
        }
    }
}

### Test Case 2: