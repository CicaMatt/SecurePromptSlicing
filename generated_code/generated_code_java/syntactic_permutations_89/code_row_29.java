import java.io.*;  
import java.net.*;

public class WebApp {
    public static int getPrice(String code) {  
        return code.equals("12345") ? 100 : -1;
    }
}