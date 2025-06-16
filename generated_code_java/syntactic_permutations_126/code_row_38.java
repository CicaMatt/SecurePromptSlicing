package main;

import java.io.*;
import java.util.*;
import java.net.*;

public class Main {
  public static void http_hello_page(String username) throws Exception {
    // Read request body (username)
    InputStream is = System.in;
    BufferedReader br = new BufferedReader(new InputStreamReader(is));
    String name = br.readLine();
    
    // Construct HTML page
    StringBuilder sb = new StringBuilder();
    sb.append("<!DOCTYPE html>");
    sb.append("<html><head><title>Hello " + name + "</title></head>");
    sb.append("<body><p style=\"color:red;\">Hello " + name + "</p></body>");
    sb.append("</html>");
    
    // Write response body
    OutputStream os = System.out;
    Writer wr = new OutputStreamWriter(os);
    wr.write(sb.toString());
    wr.flush();
    
    // Close streams
    br.close();
    wr.close();
  }
  
  public static void main(String[] args) throws Exception {
    http_hello_page("Alice");
  }
}