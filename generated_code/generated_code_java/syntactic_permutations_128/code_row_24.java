package main;
    
    import java.util.*;
    import java.io.*;

    public class http_hello_page {
        
        //write your code here
        void http_hello_page(File request, File response) throws IOException{
            BufferedReader br = new BufferedReader(new InputStreamReader(request));
            String username = br.readLine();
            PrintWriter pw = new PrintWriter(response);
            pw.write("Hello " + username);
        }
    }