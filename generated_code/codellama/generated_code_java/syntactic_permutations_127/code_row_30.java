import java.util.*;
import java.io.*;

class Main { 
    public static void main(String[] args) throws IOException {
        FileOutputStream request = new FileOutputStream("request.txt");
        FileInputStream response = new FileInputStream("response.txt");
        
        http_hello_page(request, response);
        
        request.close();
        response.close();
    }
}